#include "INCLUDES.hpp"

extern "C" {
volatile uint32_t sdram_init_stage = 0U;
volatile uint32_t sdram_init_status = HAL_OK;
volatile uint32_t sdram_fmc_clock_hz = 0U;
volatile uint32_t sdram_refresh_count = 0U;
volatile uint32_t sdram_hal_state = 0U;
}

namespace {

constexpr uint32_t kCommandTimeoutMs = 1000U;
constexpr uint32_t kRefreshRows = 8192U;
constexpr uint32_t kRefreshPeriodMs = 64U;
constexpr uint32_t kRefreshSafetyCycles = 20U;

constexpr uint32_t kModeBurstLength2 = 0x0001U;
constexpr uint32_t kModeBurstSequential = 0x0000U;
constexpr uint32_t kModeOperatingStandard = 0x0000U;
constexpr uint32_t kModeWriteBurstSingle = 0x0200U;

uint32_t command_target_from_config(void)
{
    return (hsdram1.Init.SDBank == FMC_SDRAM_BANK2)
               ? FMC_SDRAM_CMD_TARGET_BANK2
               : FMC_SDRAM_CMD_TARGET_BANK1;
}

uint32_t mode_cas_latency_from_config(void)
{
    switch (hsdram1.Init.CASLatency) {
    case FMC_SDRAM_CAS_LATENCY_1:
        return 0x0010U;
    case FMC_SDRAM_CAS_LATENCY_2:
        return 0x0020U;
    case FMC_SDRAM_CAS_LATENCY_3:
        return 0x0030U;
    default:
        return 0U;
    }
}

uint32_t fmc_clock_from_config(void)
{
    switch (__HAL_RCC_GET_FMC_SOURCE()) {
    case RCC_FMCCLKSOURCE_PLL: {
        PLL1_ClocksTypeDef clocks = {};
        HAL_RCCEx_GetPLL1ClockFreq(&clocks);
        return clocks.PLL1_Q_Frequency;
    }
    case RCC_FMCCLKSOURCE_PLL2: {
        PLL2_ClocksTypeDef clocks = {};
        HAL_RCCEx_GetPLL2ClockFreq(&clocks);
        return clocks.PLL2_R_Frequency;
    }
    case RCC_FMCCLKSOURCE_HCLK:
        return HAL_RCC_GetHCLKFreq();
    default:
        return 0U;
    }
}

uint32_t refresh_count_from_config(void)
{
    uint32_t divider;

    switch (hsdram1.Init.SDClockPeriod) {
    case FMC_SDRAM_CLOCK_PERIOD_2:
        divider = 2U;
        break;
    case FMC_SDRAM_CLOCK_PERIOD_3:
        divider = 3U;
        break;
    default:
        return 0U;
    }

    const uint32_t fmc_clock_hz = fmc_clock_from_config();
    sdram_fmc_clock_hz = fmc_clock_hz;
    if (fmc_clock_hz == 0U) {
        return 0U;
    }

    const uint64_t sd_clock_hz = fmc_clock_hz / divider;
    const uint64_t cycles =
        (sd_clock_hz * kRefreshPeriodMs) / (kRefreshRows * 1000ULL);

    if (cycles <= kRefreshSafetyCycles) {
        return 0U;
    }

    return static_cast<uint32_t>(cycles - kRefreshSafetyCycles);
}

HAL_StatusTypeDef send_command(uint32_t mode,
                               uint32_t target,
                               uint32_t auto_refresh_count,
                               uint32_t mode_register)
{
    FMC_SDRAM_CommandTypeDef command = {};
    command.CommandMode = mode;
    command.CommandTarget = target;
    command.AutoRefreshNumber = auto_refresh_count;
    command.ModeRegisterDefinition = mode_register;

    return HAL_SDRAM_SendCommand(&hsdram1, &command, kCommandTimeoutMs);
}

} // namespace

extern "C" HAL_StatusTypeDef SDRAM_InitSequence(void)
{
    sdram_init_stage = 1U;
    sdram_init_status = HAL_OK;
    sdram_hal_state = static_cast<uint32_t>(hsdram1.State);

    const uint32_t command_target = command_target_from_config();
    const uint32_t cas_latency = mode_cas_latency_from_config();
    const uint32_t refresh_count = refresh_count_from_config();
    sdram_refresh_count = refresh_count;

    if ((cas_latency == 0U) || (refresh_count == 0U)) {
        sdram_init_status = HAL_ERROR;
        return HAL_ERROR;
    }

    sdram_init_stage = 2U;
    HAL_StatusTypeDef status =
        send_command(FMC_SDRAM_CMD_CLK_ENABLE, command_target, 1U, 0U);
    if (status != HAL_OK) {
        sdram_init_status = status;
        sdram_hal_state = static_cast<uint32_t>(hsdram1.State);
        return status;
    }

    HAL_Delay(1U);

    sdram_init_stage = 3U;
    status = send_command(FMC_SDRAM_CMD_PALL, command_target, 1U, 0U);
    if (status != HAL_OK) {
        sdram_init_status = status;
        sdram_hal_state = static_cast<uint32_t>(hsdram1.State);
        return status;
    }

    sdram_init_stage = 4U;
    status = send_command(FMC_SDRAM_CMD_AUTOREFRESH_MODE,
                          command_target,
                          8U,
                          0U);
    if (status != HAL_OK) {
        sdram_init_status = status;
        sdram_hal_state = static_cast<uint32_t>(hsdram1.State);
        return status;
    }

    const uint32_t mode_register = kModeBurstLength2 |
                                   kModeBurstSequential |
                                   cas_latency |
                                   kModeOperatingStandard |
                                   kModeWriteBurstSingle;

    sdram_init_stage = 5U;
    status = send_command(FMC_SDRAM_CMD_LOAD_MODE,
                          command_target,
                          1U,
                          mode_register);
    if (status != HAL_OK) {
        sdram_init_status = status;
        sdram_hal_state = static_cast<uint32_t>(hsdram1.State);
        return status;
    }

    sdram_init_stage = 6U;
    status = HAL_SDRAM_ProgramRefreshRate(&hsdram1, refresh_count);
    sdram_init_status = status;
    sdram_hal_state = static_cast<uint32_t>(hsdram1.State);

    if (status == HAL_OK) {
        sdram_init_stage = 7U;
    }

    return status;
}
