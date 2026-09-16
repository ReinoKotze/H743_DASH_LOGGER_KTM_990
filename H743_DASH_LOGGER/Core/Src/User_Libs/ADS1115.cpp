#include "User_Libs/ADS1115.hpp"
#include "User_Libs/interrupts.h"

extern "C" {
volatile uint32_t ads1115_i2c_error_count = 0U;
volatile uint32_t ads1115_conversion_timeout_count = 0U;
volatile uint32_t ads1115_sample_count = 0U;
volatile uint32_t ads1115_last_hal_status = 0U;
volatile uint32_t ads1115_last_hal_error = 0U;
volatile uint32_t ads1115_last_error_stage = 0U;
volatile uint32_t ads1115_last_config_written = 0U;
volatile uint32_t ads1115_last_config_read = 0U;
volatile uint32_t ads1115_config_read_count = 0U;
}

namespace ADS1115 {
namespace {

constexpr uint8_t ConversionRegister = 0x00U;
constexpr uint8_t ConfigRegister = 0x01U;
constexpr uint8_t LowThresholdRegister = 0x02U;
constexpr uint8_t HighThresholdRegister = 0x03U;
constexpr uint16_t DeviceAddress = static_cast<uint16_t>(Address7Bit << 1U);
constexpr uint32_t I2cTimeoutMs = 10U;
constexpr uint32_t SampleIntervalMs = 50U; // Alternate channels: 10 samples/s each.
constexpr uint32_t ConversionTimeoutMs = 10U;
constexpr uint32_t ErrorBackoffMs = 500U;
constexpr int32_t FullScaleMillivolts = 6144; // PGA = +/-6.144 V.

I2C_HandleTypeDef *bus = nullptr;
bool ready = false;
bool converting = false;
uint8_t activeChannel = EngineChannel;
uint8_t nextChannel = EngineChannel;
uint32_t conversionStartedMs = 0U;
uint32_t lastStartMs = 0U;
uint32_t lastPollMs = 0U;
uint32_t retryAfterMs = 0U;
uint32_t lastSetupAttemptMs = 0U;
int32_t latestMillivolts[2] = {};
uint32_t latestSampleMs[2] = {};
bool sampleValid[2] = {};

int indexForChannel(uint8_t channel)
{
    if (channel == EngineChannel) return 0;
    if (channel == AmbientChannel) return 1;
    return -1;
}

void recordI2cFailure(HAL_StatusTypeDef status, uint32_t stage)
{
    ++ads1115_i2c_error_count;
    ads1115_last_hal_status = static_cast<uint32_t>(status);
    ads1115_last_hal_error = bus != nullptr ? HAL_I2C_GetError(bus) : 0U;
    ads1115_last_error_stage = stage;
}

} // namespace

bool ReadRegister(uint8_t reg, uint16_t *value)
{
    if (bus == nullptr || value == nullptr || reg > HighThresholdRegister) return false;
    uint8_t bytes[2] = {};
    const HAL_StatusTypeDef status = HAL_I2C_Mem_Read(
        bus, DeviceAddress, reg, I2C_MEMADD_SIZE_8BIT,
        bytes, sizeof(bytes), I2cTimeoutMs);
    if (status != HAL_OK) {
        recordI2cFailure(status, 0x10U + reg);
        return false;
    }
    *value = static_cast<uint16_t>((static_cast<uint16_t>(bytes[0]) << 8U) | bytes[1]);
    return true;
}

bool WriteRegister(uint8_t reg, uint16_t value)
{
    if (bus == nullptr || reg > HighThresholdRegister) return false;
    uint8_t bytes[2] = {
        static_cast<uint8_t>(value >> 8U), static_cast<uint8_t>(value)
    };
    const HAL_StatusTypeDef status = HAL_I2C_Mem_Write(
        bus, DeviceAddress, reg, I2C_MEMADD_SIZE_8BIT,
        bytes, sizeof(bytes), I2cTimeoutMs);
    if (status != HAL_OK) {
        recordI2cFailure(status, 0x20U + reg);
        return false;
    }
    return true;
}

bool Setup(I2C_HandleTypeDef *i2c)
{
    bus = i2c;
    lastSetupAttemptMs = HAL_GetTick();
    ready = false;
    converting = false;
    sampleValid[0] = false;
    sampleValid[1] = false;
    if (bus == nullptr) {
        recordI2cFailure(HAL_ERROR, 1U);
        return false;
    }
    const HAL_StatusTypeDef status = HAL_I2C_IsDeviceReady(bus, DeviceAddress, 2U, I2cTimeoutMs);
    if (status != HAL_OK) {
        recordI2cFailure(status, 1U);
        return false;
    }

    // MSB(Hi)=1 and MSB(Lo)=0 select conversion-ready mode.
    if (!WriteRegister(LowThresholdRegister, 0x0000U) ||
        !WriteRegister(HighThresholdRegister, 0x8000U)) return false;

    nextChannel = EngineChannel;
    lastStartMs = HAL_GetTick() - SampleIntervalMs;
    retryAfterMs = 0U;
    ADS1115_alert_ready_due = 0U;
    ready = true;
    return true;
}

bool StartConversion(uint8_t channel)
{
    if (!ready || converting || indexForChannel(channel) < 0) return false;

    // OS=1, single-ended AINx, PGA +/-6.144 V, single-shot, 860 SPS,
    // active-low ALERT/RDY enabled after one conversion.
    const uint16_t mux = static_cast<uint16_t>((4U + channel) << 12U);
    const uint16_t config = static_cast<uint16_t>(0x8000U | mux | 0x0100U | 0x00E0U);
    ads1115_last_config_written = config;
    ADS1115_alert_ready_due = 0U;
    if (!WriteRegister(ConfigRegister, config)) {
        retryAfterMs = HAL_GetTick() + ErrorBackoffMs;
        return false;
    }

    activeChannel = channel;
    converting = true;
    conversionStartedMs = HAL_GetTick();
    lastStartMs = conversionStartedMs;
    return true;
}

void Service()
{
    const uint32_t now = HAL_GetTick();
    if (!ready) {
        if (bus != nullptr && now - lastSetupAttemptMs >= 1000U) {
            (void)Setup(bus);
        }
        return;
    }
    if (retryAfterMs != 0U) {
        if (static_cast<int32_t>(now - retryAfterMs) < 0) return;
        retryAfterMs = 0U;
    }

    if (converting)
    {
        const uint32_t elapsed = now - conversionStartedMs;
        // The pin is the normal completion path. Poll OS after 3 ms as a
        // fallback if an interrupt edge was missed or ALERT/RDY is unwired.
        if (ADS1115_alert_ready_due == 0U && elapsed < 3U) return;

        if (now == lastPollMs) return;
        lastPollMs = now;

        uint16_t config = 0U;
        if (!ReadRegister(ConfigRegister, &config))
        {
            converting = false;
            retryAfterMs = HAL_GetTick() + ErrorBackoffMs;
            return;
        }
        ads1115_last_config_read = config;
        ++ads1115_config_read_count;
        if ((config & 0x8000U) != 0U)
        {
            uint16_t raw = 0U;
            if (!ReadRegister(ConversionRegister, &raw))
            {
                converting = false;
                retryAfterMs = HAL_GetTick() + ErrorBackoffMs;
                return;
            }
            const int16_t signedRaw = static_cast<int16_t>(raw);
            const int index = indexForChannel(activeChannel);
            const int32_t measuredMillivolts =
                static_cast<int32_t>(signedRaw) * FullScaleMillivolts / 32768;
            latestMillivolts[index] = measuredMillivolts > 0 ? measuredMillivolts : 0;
            latestSampleMs[index] = HAL_GetTick();
            sampleValid[index] = true;
            ++ads1115_sample_count;
            converting = false;
            ADS1115_alert_ready_due = 0U;
            nextChannel = activeChannel == EngineChannel ? AmbientChannel : EngineChannel;
            return;
        }
        ADS1115_alert_ready_due = 0U;
        if (elapsed >= ConversionTimeoutMs)
        {
            converting = false;
            ADS1115_alert_ready_due = 0U;
            ++ads1115_conversion_timeout_count;
            retryAfterMs = HAL_GetTick() + ErrorBackoffMs;
        }
        return;
    }

    if (now - lastStartMs >= SampleIntervalMs)
    {
        (void)StartConversion(nextChannel);
        // Limit retries when the I2C bus or ADC is unavailable.
        if (!converting) lastStartMs = now;
    }
}

bool ReadMillivolts(uint8_t channel, int32_t *millivolts)
{
    const int index = indexForChannel(channel);
    if (index < 0 || millivolts == nullptr || !sampleValid[index] ||
        HAL_GetTick() - latestSampleMs[index] > 1000U) return false;
    *millivolts = latestMillivolts[index];
    return true;
}

} // namespace ADS1115

