#include "MCP2518FD.hpp"
#include "interrupts.hpp"
#include <string.h>

namespace MCP2518FD {
volatile SetupStatus setup_status = SetupStatus::NotStarted;
volatile uint32_t last_hal_status = HAL_OK;
volatile uint32_t last_hal_error = 0U;
volatile uint32_t last_osc = 0U;
volatile uint32_t last_cicon = 0U;
volatile uint32_t device_id = 0U;
volatile uint32_t rx_count = 0U, rx_dropped = 0U, rx_overflows = 0U;
volatile uint32_t tx_queued = 0U, last_trec = 0U;

namespace {
constexpr uint16_t CiCon = 0x000U;
constexpr uint16_t Osc = 0xE00U;
constexpr uint16_t DevId = 0xE14U;
constexpr uint32_t TimeoutMs = 100U;
SPI_HandleTypeDef *bus = nullptr;
constexpr uint16_t TxCon = 0x05C, RxCon = 0x068;
constexpr uint32_t NominalTiming = (30UL << 16) | (7UL << 8) | 7UL;
constexpr uint32_t DataTiming = (6UL << 16) | (1UL << 8) | 1UL;
static_assert(20000000 / (1 + 31 + 8) == 500000, "Nominal timing");
static_assert(20000000 / (1 + 7 + 2) == 2000000, "Data timing");
// 8 objects per configured FIFO, plus the remaining reset-default FIFOs.
static_assert(2 * 8 * 72 + 29 * 16 <= 2048, "Message RAM capacity");
Frame received[8] = {};
uint8_t head = 0, tail = 0, queued = 0;
uint32_t lastPoll = 0;


bool transfer(uint8_t *tx, uint8_t *rx, uint16_t count)
{
    HAL_GPIO_WritePin(CAN_CS_GPIO_Port, CAN_CS_Pin, GPIO_PIN_RESET);
    const HAL_StatusTypeDef result = HAL_SPI_TransmitReceive(bus, tx, rx, count, 10U);
    HAL_GPIO_WritePin(CAN_CS_GPIO_Port, CAN_CS_Pin, GPIO_PIN_SET);
    last_hal_status = result;
    last_hal_error = HAL_SPI_GetError(bus);
    if (result != HAL_OK) {
        setup_status = SetupStatus::SpiError;
        return false;
    }
    return true;
}

bool read32(uint16_t address, uint32_t &value)
{
    uint8_t tx[6] = {static_cast<uint8_t>(0x30U | (address >> 8U)),
                     static_cast<uint8_t>(address), 0U, 0U, 0U, 0U};
    uint8_t rx[6] = {};
    if (!transfer(tx, rx, sizeof(tx))) return false;
    // Registers are byte-addressed, least-significant byte at lowest address.
    value = static_cast<uint32_t>(rx[2]) |
            (static_cast<uint32_t>(rx[3]) << 8U) |
            (static_cast<uint32_t>(rx[4]) << 16U) |
            (static_cast<uint32_t>(rx[5]) << 24U);
    return true;
}

bool write8(uint16_t address, uint8_t value)
{
    uint8_t tx[3] = {static_cast<uint8_t>(0x20U | (address >> 8U)),
                     static_cast<uint8_t>(address), value};
    uint8_t rx[3] = {};
    return transfer(tx, rx, sizeof(tx));
}

bool write32(uint16_t address, uint32_t value)
{
    uint8_t tx[6] = {static_cast<uint8_t>(0x20U | (address >> 8)),
                    static_cast<uint8_t>(address)};
    uint8_t rx[6] = {};
    for (unsigned i = 0; i < 4; ++i) tx[i + 2] = static_cast<uint8_t>(value >> (8 * i));
    return transfer(tx, rx, sizeof(tx));
}

bool verifiedWrite(uint16_t address, uint32_t value, uint32_t mask = 0xFFFFFFFFUL)
{
    uint32_t actual;
    if (!write32(address, value) || !read32(address, actual)) return false;
    if ((actual & mask) == (value & mask)) return true;
    setup_status = SetupStatus::ReadbackError;
    return false;
}

bool ramTransfer(uint32_t offset, uint8_t *data, bool write)
{
    if ((offset & 3U) != 0U || offset > 2048U - 72U) {
        setup_status = SetupStatus::ReadbackError;
        return false;
    }
    const uint16_t address = static_cast<uint16_t>(0x400U + offset);
    uint8_t tx[74] = {}, rx[74] = {};
    tx[0] = static_cast<uint8_t>((write ? 0x20U : 0x30U) | (address >> 8));
    tx[1] = static_cast<uint8_t>(address);
    if (write) memcpy(tx + 2, data, 72);
    if (!transfer(tx, rx, sizeof(tx))) return false;
    if (!write) memcpy(data, rx + 2, 72);
    return true;
}

uint32_t word(const uint8_t *bytes)
{
    return uint32_t(bytes[0]) | (uint32_t(bytes[1]) << 8) |
           (uint32_t(bytes[2]) << 16) | (uint32_t(bytes[3]) << 24);
}
constexpr uint8_t lengths[16] = {0,1,2,3,4,5,6,7,8,12,16,20,24,32,48,64};

bool waitClock()
{
    const uint32_t start = HAL_GetTick();
    do {
        uint32_t value;
        if (!read32(Osc, value)) return false;
        last_osc = value;
        // Reject stuck-high MISO as well as waiting for OSCRDY.
        if ((value & 0xFFFFE000U) == 0U && (value & (1UL << 10U)) != 0U)
            return true;
        HAL_Delay(1U);
    } while (HAL_GetTick() - start < TimeoutMs);
    setup_status = SetupStatus::ClockTimeout;
    return false;
}

bool waitConfiguration()
{
    const uint32_t start = HAL_GetTick();
    do {
        uint32_t value;
        if (!read32(CiCon, value)) return false;
        last_cicon = value;
        if (((value >> 21U) & 7U) == 4U) return true;
        HAL_Delay(1U);
    } while (HAL_GetTick() - start < TimeoutMs);
    setup_status = SetupStatus::ConfigurationTimeout;
    return false;
}
} // namespace

bool Setup(SPI_HandleTypeDef *spi)
{
    setup_status = SetupStatus::InProgress;
    head = tail = queued = 0;
    rx_count = rx_dropped = rx_overflows = tx_queued = last_trec = 0U;
    last_hal_status = HAL_OK;
    last_hal_error = last_osc = last_cicon = device_id = 0U;
    HAL_GPIO_WritePin(CAN_CS_GPIO_Port, CAN_CS_Pin, GPIO_PIN_SET);
    if (spi == nullptr || spi->Instance != SPI1 ||
        HAL_SPI_GetState(spi) != HAL_SPI_STATE_READY ||
        spi->Init.Mode != SPI_MODE_MASTER || spi->Init.Direction != SPI_DIRECTION_2LINES ||
        spi->Init.DataSize != SPI_DATASIZE_8BIT || spi->Init.FirstBit != SPI_FIRSTBIT_MSB ||
        spi->Init.CLKPolarity != SPI_POLARITY_LOW || spi->Init.CLKPhase != SPI_PHASE_1EDGE ||
        spi->Init.NSS != SPI_NSS_SOFT || spi->Init.NSSPMode != SPI_NSS_PULSE_DISABLE) {
        setup_status = SetupStatus::InvalidSpi;
        return false;
    }
    bus = spi;
    // Conservative startup speed, including a 4 MHz crystal before PLL setup.
    // Leave this speed in place; change it only after oscillator configuration.
    bus->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
    const HAL_StatusTypeDef status = HAL_SPI_Init(bus);
    last_hal_status = status;
    last_hal_error = HAL_SPI_GetError(bus);
    if (status != HAL_OK) {
        setup_status = SetupStatus::SpiError;
        return false;
    }
    HAL_Delay(10U);
    if (!waitClock()) return false;

    // RESET is only valid in Configuration mode. Preserve other byte-3 fields.
    uint32_t control;
    if (!read32(CiCon, control) ||
        !write8(CiCon + 3U, static_cast<uint8_t>(((control >> 24U) & 0xF8U) | 4U)) ||
        !waitConfiguration()) return false;
    uint8_t reset[2] = {0U, 0U};
    uint8_t ignored[2] = {};
    if (!transfer(reset, ignored, sizeof(reset))) return false;
    HAL_Delay(10U);
    if (!waitClock() || !waitConfiguration()) return false;

    // Exercise MOSI and MISO by changing only the CLKO divider, then restoring it.
    const uint8_t original = static_cast<uint8_t>(last_osc);
    const uint8_t probe = original ^ 0x20U;
    if (!write8(Osc, probe)) return false;
    uint32_t readback;
    const bool readOk = read32(Osc, readback);
    const bool restored = write8(Osc, original);
    if (!readOk || !restored) {
        setup_status = SetupStatus::SpiError;
        return false;
    }
    if (static_cast<uint8_t>(readback) != probe) {
        setup_status = SetupStatus::ReadbackError;
        return false;
    }
    uint32_t id;
    if (!read32(DevId, id)) return false;
    device_id = id;
    // 20 MHz crystal directly supplies SYSCLK: PLL off, divide-by-two off.
    if (!write8(Osc, 0x60U) || !waitClock()) return false;
    if ((last_osc & 0x111U) != 0U) {
        setup_status = SetupStatus::ReadbackError;
        return false;
    }

    // Configuration mode, ISO CRC on, BRS enabled, TXQ/TEF disabled.
    // Nominal: 40 TQ/bit, 80% sample point, SJW 8 TQ.
    // Data: 10 TQ/bit, 80% sample point, SJW 2 TQ.
    if (!verifiedWrite(CiCon, 0x04000020U, 0xFF1FFFFFUL) ||
        !verifiedWrite(0x004, NominalTiming) ||
        !verifiedWrite(0x008, DataTiming) ||
        !verifiedWrite(0x00C, (2UL << 16) | (8UL << 8), 0x00037F00U) ||
        !write8(0xE0C, 1U)) return false; // ECC enabled before RAM initialization.
    for (uint16_t address = 0x400; address < 0xC00; address += 4)
        if (!write32(address, 0U)) return false;

    // FIFO1: TX, FIFO2: RX; eight 64-byte payload slots each, no timestamps.
    if (!verifiedWrite(TxCon, 0xE7000080U, 0xFF7F00FFU) ||
        !verifiedWrite(RxCon, 0xE7000001U, 0xFF7F00FFU) ||
        !write32(0x1D0, 0U) || // Filter 0 disabled while changing it.
        !verifiedWrite(0x1F0, 0U) || // Accept any standard or extended ID.
        !verifiedWrite(0x1F4, 0U) ||
        !write8(0x1D0, 0x82U)) return false; // Filter 0 enabled -> FIFO2.

    CAN_int_due = 0U;
    if (!write32(0x01C, 1UL << 17) || // Enable only RX interrupt.
        !write8(CiCon + 3, 0U)) return false; // Normal ISO CAN FD.
    const uint32_t start = HAL_GetTick();
    do {
        uint32_t txControl, rxControl;
        if (!read32(CiCon, control) || !read32(TxCon, txControl) ||
            !read32(RxCon, rxControl)) return false;
        last_cicon = control;
        if (((control >> 21) & 7U) == 0U &&
            ((txControl | rxControl) & (1UL << 10)) == 0U) {
            setup_status = SetupStatus::Ready;
            lastPoll = HAL_GetTick();
            return true;
        }
        HAL_Delay(1U);
    } while (HAL_GetTick() - start < TimeoutMs);
    setup_status = SetupStatus::NormalModeTimeout;
    return false;
}
// All public operations run on the main loop, never concurrently or in an ISR.
bool Send(const Frame &frame)
{
    if (setup_status != SetupStatus::Ready || frame.remote ||
        frame.id > (frame.extended ? 0x1FFFFFFFUL : 0x7FFUL) ||
        (!frame.fd && (frame.length > 8 || frame.brs))) return false;
    uint8_t dlc = 0;
    while (dlc < 16 && lengths[dlc] != frame.length) ++dlc;
    if (dlc == 16) return false;
    uint32_t status, offset;
    if (!read32(TxCon + 4, status) || (status & 1U) == 0U ||
        !read32(TxCon + 8, offset)) return false;
    uint8_t object[72] = {};
    const uint32_t id = frame.extended ?
        ((frame.id >> 18) | ((frame.id & 0x3FFFFUL) << 11)) : frame.id;
    for (unsigned i = 0; i < 4; ++i) object[i] = static_cast<uint8_t>(id >> (8 * i));
    object[4] = dlc | (frame.extended ? 0x10 : 0) |
                (frame.brs ? 0x40 : 0) | (frame.fd ? 0x80 : 0);
    memcpy(object + 8, frame.data, frame.length);
    if (!ramTransfer(offset, object, true) || !write8(TxCon + 1, 3U)) return false;
    ++tx_queued; // Accepted by controller, not proof of bus delivery.
    return true;
}

void Service()
{
    if (setup_status != SetupStatus::Ready) return;
    const uint32_t now = HAL_GetTick();
    if (!CAN_int_due && HAL_GPIO_ReadPin(CAN_INT_GPIO_Port, CAN_INT_Pin) != GPIO_PIN_RESET &&
        now - lastPoll < 10U) return;
    CAN_int_due = 0U;
    lastPoll = now;
    uint32_t errors;
    if (!read32(0x034, errors)) return;
    last_trec = errors; // Includes TEC, REC and bus-off status.
    // Bound work per call so display/tasks still run under sustained traffic.
    for (unsigned n = 0; n < 4; ++n) {
        uint32_t status, offset;
        if (!read32(RxCon + 4, status)) return;
        if (status & 8U) {
            ++rx_overflows;
            if (!write8(RxCon + 4, 0xF7U)) return;
        }
        if (!(status & 1U)) return;
        if (!read32(RxCon + 8, offset)) return;
        uint8_t object[72] = {};
        if (!ramTransfer(offset, object, false)) return;
        Frame frame = {};
        const uint32_t rawId = word(object);
        const uint8_t flags = object[4];
        frame.extended = (flags & 0x10U) != 0;
        frame.remote = (flags & 0x20U) != 0;
        frame.brs = (flags & 0x40U) != 0;
        frame.fd = (flags & 0x80U) != 0;
        frame.id = frame.extended ?
            ((rawId & 0x7FFU) << 18) | ((rawId >> 11) & 0x3FFFFU) : rawId & 0x7FFU;
        frame.length = lengths[flags & 0xFU];
        if (!frame.fd && frame.length > 8) frame.length = 8;
        if (!frame.remote) memcpy(frame.data, object + 8, frame.length);
        if (!write8(RxCon + 1, 1U)) return; // UINC releases the hardware entry.
        ++rx_count;
        if (queued < 8) {
            received[head] = frame;
            head = (head + 1) % 8;
            ++queued;
        } else ++rx_dropped; // Drop newest, continue draining the hardware FIFO.
    }
    CAN_int_due = 1U; // Continue next loop even if INT never produces a new edge.
}

bool Receive(Frame &frame)
{
    if (!queued) return false;
    frame = received[tail];
    tail = (tail + 1) % 8;
    --queued;
    return true;
}
} // namespace MCP2518FD
