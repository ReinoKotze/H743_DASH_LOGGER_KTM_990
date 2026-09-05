

#include "User_Libs/bsp_sdram.h"

extern SDRAM_HandleTypeDef hsdram1;

#define SDRAM_REFRESH_COUNT  296U

HAL_StatusTypeDef SDRAM_InitSequence(void)
{
    FMC_SDRAM_CommandTypeDef command = {0};
    uint32_t mode_register;

    command.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
    command.CommandTarget = FMC_COMMAND_TARGET_BANK;
    command.AutoRefreshNumber = 1U;
    command.ModeRegisterDefinition = 0U;

    if (HAL_SDRAM_SendCommand(&hsdram1, &command, SDRAM_TIMEOUT) != HAL_OK) {
        return HAL_ERROR;
    }

    HAL_Delay(1U);

    command.CommandMode = FMC_SDRAM_CMD_PALL;
    command.CommandTarget = FMC_COMMAND_TARGET_BANK;
    command.AutoRefreshNumber = 1U;
    command.ModeRegisterDefinition = 0U;

    if (HAL_SDRAM_SendCommand(&hsdram1, &command, SDRAM_TIMEOUT) != HAL_OK) {
        return HAL_ERROR;
    }

    command.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
    command.CommandTarget = FMC_COMMAND_TARGET_BANK;
    command.AutoRefreshNumber = 8U;
    command.ModeRegisterDefinition = 0U;

    if (HAL_SDRAM_SendCommand(&hsdram1, &command, SDRAM_TIMEOUT) != HAL_OK) {
        return HAL_ERROR;
    }

    /* Vendor mode: burst length 2 and CAS 3; FMC read burst is disabled. */
    mode_register = SDRAM_MODEREG_BURST_LENGTH_2 |
                    SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL |
					SDRAM_MODEREG_CAS_LATENCY_3 |
                    SDRAM_MODEREG_OPERATING_MODE_STANDARD |
                    SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

    command.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
    command.CommandTarget = FMC_COMMAND_TARGET_BANK;
    command.AutoRefreshNumber = 1U;
    command.ModeRegisterDefinition = mode_register;

    if (HAL_SDRAM_SendCommand(&hsdram1, &command, SDRAM_TIMEOUT) != HAL_OK) {
        return HAL_ERROR;
    }

    /*
     * FMC kernel clock: 121.6 MHz; SDCLK = FMC / 3 = 40.533 MHz. 
     * W9825G6KH: 8192 refreshes / 64 ms up to 85 C.
     * floor(40.533 MHz * 7.8125 us) - 20 = 296.
     * Above 85 C the datasheet requires 16 ms / 8192 refresh.
     */
    if (HAL_SDRAM_ProgramRefreshRate(&hsdram1,
                                     SDRAM_REFRESH_COUNT) != HAL_OK) {
        return HAL_ERROR;
    }

    return HAL_OK;
}

