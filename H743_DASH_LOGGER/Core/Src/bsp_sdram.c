#include "bsp_sdram.h"

extern SDRAM_HandleTypeDef hsdram1;

#define SDRAM_REFRESH_COUNT  370U

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
    command.AutoRefreshNumber = 4U;
    command.ModeRegisterDefinition = 0U;

    if (HAL_SDRAM_SendCommand(&hsdram1, &command, SDRAM_TIMEOUT) != HAL_OK) {
        return HAL_ERROR;
    }

    mode_register = SDRAM_MODEREG_BURST_LENGTH_2 |
                    SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL |
					SDRAM_MODEREG_CAS_LATENCY_2 |
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
     * FMC kernel clock: 100 MHz
     * SDRAM clock period: 2 -> 50 MHz SDRAM clock
     * Refresh count = (50 MHz * 7.8125 us) - 20 = 370.625
     */
    if (HAL_SDRAM_ProgramRefreshRate(&hsdram1,
                                     SDRAM_REFRESH_COUNT) != HAL_OK) {
        return HAL_ERROR;
    }

    return HAL_OK;
}
