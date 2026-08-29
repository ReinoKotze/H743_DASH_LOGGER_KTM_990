/*
 * w25q128.c
 *
 *  Created on: 26 Aug 2026
 *      Author: reino
 */
#include "w25q128.h"
#include "quadspi.h"
#include "main.h"

static uint8_t QSPI_WriteEnable(void);
uint8_t QSPI_AutoPollingMemReady(uint32_t timeout_ms);
static uint8_t QSPI_Configuration(void);
static uint8_t QSPI_ResetChip(void);
uint8_t QSPI_AutoPollingMemReady(uint32_t timeout_ms);
uint8_t CSP_QSPI_ReadStatusRegister(uint8_t command, uint8_t *status);


//volatile uint32_t qspi_init_step;
//volatile uint32_t qspi_init_status;
//volatile uint32_t qspi_hal_error;
//volatile uint32_t qspi_hal_state;
//uint8_t qspi_status_reg1;


uint8_t CSP_QUADSPI_Init(void) {


    if (QSPI_ResetChip() != HAL_OK) {
        return HAL_ERROR;
    }

    /* Do not send the SR2/QE command until reset has completed. */
    if (QSPI_AutoPollingMemReady(W25Q128_READY_TIMEOUT_MS) != HAL_OK) {
        return HAL_ERROR;
    }

    /* Read SR2 and set QE only when it is not already enabled. */
    return QSPI_Configuration();

}

uint8_t CSP_QSPI_Erase_Chip(void) {

    QSPI_CommandTypeDef sCommand = {0};

    if (QSPI_WriteEnable() != HAL_OK)
    {
        return HAL_ERROR;
    }

    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = CHIP_ERASE_CMD; /* 0xC7 */
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_NONE;
    sCommand.DummyCycles       = 0;
    sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(&hqspi, &sCommand,
                         HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }

    return QSPI_AutoPollingMemReady(W25Q128_CHIP_ERASE_TIMEOUT_MS);
}

static uint8_t QSPI_WriteEnable(void) {
	QSPI_CommandTypeDef sCommand = { 0 };
	QSPI_AutoPollingTypeDef sConfig = { 0 };


	/* Enable write operations ------------------------------------------ */
	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction = WRITE_ENABLE_CMD;
	sCommand.AddressMode = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = QSPI_DATA_NONE;
	sCommand.DummyCycles = 0;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	if (( HAL_QSPI_Command(&hqspi, &sCommand,
			HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK) {
		return HAL_ERROR;
	}

	/* Configure automatic polling mode to wait for write enabling ---- */
	sConfig.Match = 0x02;
	sConfig.Mask = 0x02;
	sConfig.MatchMode = QSPI_MATCH_MODE_AND;
	sConfig.StatusBytesSize = 1;
	sConfig.Interval = 0x10;
	sConfig.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;

	sCommand.Instruction = READ_STATUS_REG_CMD;
	sCommand.DataMode = QSPI_DATA_1_LINE;

	 return HAL_QSPI_AutoPolling(&hqspi, &sCommand, &sConfig,
	                                W25Q128_READY_TIMEOUT_MS);
}
/*Enable quad mode*/
/* Las versiones acabadas en IQ lo llevan activado por defecto, como en mi caso. */



static uint8_t QSPI_Configuration(void)
{
    uint8_t status_reg2;
    uint8_t new_status_reg2;
	QSPI_CommandTypeDef sCommand = {0};
	//new_status_reg2 = status_reg2 | 0x02U;

	    /* Read Status Register-2. */
	    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
	    sCommand.Instruction       = READ_STATUS_REG2_CMD; /* 0x35 */
	    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
	    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	    sCommand.DataMode          = QSPI_DATA_1_LINE;
	    sCommand.NbData            = 1U;
	    sCommand.DummyCycles       = 0U;
	    sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
	    sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
	    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

	    if (HAL_QSPI_Command(&hqspi, &sCommand,
	                         HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	    {
	        return HAL_ERROR;
	    }

	    if (HAL_QSPI_Receive(&hqspi, &status_reg2,
	                         HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	    {
	        return HAL_ERROR;
	    }

	    /*
	     * Bit 1: QE  = 1, enable quad operation.
	     * Bit 6: CMP = 0, disable inverted protection.
	     *
	     * Your current Status Register-2 is 0x42.
	     * This changes it to 0x02.
	     */
	    new_status_reg2 = status_reg2 | 0x02U;
	    //new_status_reg2 &= ~0x40U;

	    if (new_status_reg2 == status_reg2)
	    {
	        return HAL_OK;
	    }

	    if (QSPI_WriteEnable() != HAL_OK)
	    {
	        return HAL_ERROR;
	    }

	    sCommand.Instruction = WRITE_STATUS_REG2_CMD; /* 0x31 */
	    sCommand.DataMode    = QSPI_DATA_1_LINE;
	    sCommand.NbData      = 1;

	    if (HAL_QSPI_Command(&hqspi, &sCommand,
	                         HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	    {
	        return HAL_ERROR;
	    }

	    if (HAL_QSPI_Transmit(&hqspi, &new_status_reg2,
	                          HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	    {
	        return HAL_ERROR;
	    }

	    if (QSPI_AutoPollingMemReady(W25Q128_READY_TIMEOUT_MS) != HAL_OK)
	    {
	        return HAL_ERROR;
	    }

	    return HAL_OK;
}

uint8_t CSP_QSPI_EraseBlock(uint32_t flash_address)
{
    QSPI_CommandTypeDef sCommand = {0};

    if (flash_address >= MEMORY_FLASH_SIZE)
    {
        return HAL_ERROR;
    }

    /* Erase the 64 KiB block containing flash_address. */
    flash_address &= ~(MEMORY_BLOCK_SIZE - 1U);

    if (QSPI_WriteEnable() != HAL_OK)
    {
        return HAL_ERROR;
    }

    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = BLOCK_ERASE_CMD; /* 0xD8 */
    sCommand.AddressMode       = QSPI_ADDRESS_1_LINE;
    sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
    sCommand.Address           = flash_address;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_NONE;
    sCommand.DummyCycles       = 0;
    sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(&hqspi, &sCommand,
                         HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }

    return QSPI_AutoPollingMemReady(W25Q128_READY_TIMEOUT_MS);
}

uint8_t CSP_QSPI_EraseSector(uint32_t EraseStartAddress,
                             uint32_t EraseEndAddress)
{
    QSPI_CommandTypeDef sCommand = {0};

    if ((EraseStartAddress >= MEMORY_FLASH_SIZE) ||
        (EraseEndAddress >= MEMORY_FLASH_SIZE) ||
        (EraseStartAddress > EraseEndAddress))
    {
        return HAL_ERROR;
    }

    EraseStartAddress &= ~(MEMORY_SECTOR_SIZE - 1U);

    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = SECTOR_ERASE_CMD; /* 0x20 */
    sCommand.AddressMode       = QSPI_ADDRESS_1_LINE;
    sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_NONE;
    sCommand.DummyCycles       = 0;
    sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    while (EraseStartAddress <= EraseEndAddress)
    {
        if (QSPI_WriteEnable() != HAL_OK)
        {
            return HAL_ERROR;
        }

        sCommand.Address = EraseStartAddress;

        if (HAL_QSPI_Command(&hqspi, &sCommand,
                             HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            return HAL_ERROR;
        }

        if (QSPI_AutoPollingMemReady(W25Q128_READY_TIMEOUT_MS) != HAL_OK)
        {
            return HAL_ERROR;
        }

        EraseStartAddress += MEMORY_SECTOR_SIZE;
    }

    return HAL_OK;
}

uint8_t CSP_QSPI_WriteMemory(uint8_t *buffer, uint32_t address,
                             uint32_t buffer_size)
{
    QSPI_CommandTypeDef sCommand = {0};
    uint32_t bytes_this_page;
    uint32_t remaining = buffer_size;

    if ((buffer == NULL) || (buffer_size == 0U) ||
        (address >= MEMORY_FLASH_SIZE) ||
        (buffer_size > (MEMORY_FLASH_SIZE - address)))
    {
        return HAL_ERROR;
    }

    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = QUAD_IN_FAST_PROG_CMD; /* 0x32 */
    sCommand.AddressMode       = QSPI_ADDRESS_1_LINE;
    sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_4_LINES;
    sCommand.DummyCycles       = 0;
    sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    while (remaining > 0U)
    {
        bytes_this_page = MEMORY_PAGE_SIZE -
                          (address % MEMORY_PAGE_SIZE);

        if (bytes_this_page > remaining)
        {
            bytes_this_page = remaining;
        }

        if (QSPI_WriteEnable() != HAL_OK)
        {
            return HAL_ERROR;
        }

        sCommand.Address = address;
        sCommand.NbData  = bytes_this_page;

        if (HAL_QSPI_Command(&hqspi, &sCommand,
                             HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            return HAL_ERROR;
        }

        if (HAL_QSPI_Transmit(&hqspi, buffer,
                              HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        {
            return HAL_ERROR;
        }

        if (QSPI_AutoPollingMemReady(W25Q128_READY_TIMEOUT_MS) != HAL_OK)
        {
            return HAL_ERROR;
        }

        address   += bytes_this_page;
        buffer    += bytes_this_page;
        remaining -= bytes_this_page;
    }

    return HAL_OK;
}

uint8_t CSP_QSPI_DisableMemoryMappedMode(void)
{
    return (HAL_QSPI_Abort(&hqspi) == HAL_OK) ? HAL_OK : HAL_ERROR;
}

uint8_t CSP_QSPI_EnableMemoryMappedMode(void)
{
    QSPI_CommandTypeDef sCommand = {0};
    QSPI_MemoryMappedTypeDef sMemMappedCfg = {0};


    if (QSPI_AutoPollingMemReady(W25Q128_READY_TIMEOUT_MS) != HAL_OK) {
          return HAL_ERROR;
      }
    /*
     * 0x6B: Quad Output Fast Read
     * Instruction: 1 line, address: 1 line, data: 4 lines, 8 dummy clocks.
     */
        sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
        sCommand.Instruction       = QUAD_OUT_FAST_READ_CMD; /* 0x6B */
        sCommand.AddressMode       = QSPI_ADDRESS_1_LINE;
        sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
        sCommand.Address           = 0U;
        sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
        sCommand.DataMode          = QSPI_DATA_4_LINES;
        sCommand.NbData            = 0U;
        sCommand.DummyCycles       = DUMMY_CLOCK_CYCLES_READ_QUAD; /* 8 */
        sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
        sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
        sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    sMemMappedCfg.TimeOutActivation = QSPI_TIMEOUT_COUNTER_DISABLE;
    sMemMappedCfg.TimeOutPeriod     = 0U;

    if (HAL_QSPI_MemoryMapped(&hqspi, &sCommand, &sMemMappedCfg) != HAL_OK)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

static uint8_t QSPI_ResetChip(void)
{
    QSPI_CommandTypeDef sCommand = {0};

    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_NONE;
    sCommand.DummyCycles       = 0U;
    sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    sCommand.Instruction = RESET_ENABLE_CMD;  /* 0x66 */

    if (HAL_QSPI_Command(&hqspi, &sCommand,
                         HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        return HAL_ERROR;
    }

    sCommand.Instruction = RESET_EXECUTE_CMD; /* 0x99 */

    if (HAL_QSPI_Command(&hqspi, &sCommand,
                         HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) {
        return HAL_ERROR;
    }

    HAL_Delay(1U);  /* Allow flash reset recovery */
    return HAL_OK;
}

uint8_t CSP_QSPI_Read(uint8_t *pData, uint32_t ReadAddr, uint32_t Size)
{
    QSPI_CommandTypeDef sCommand = {0};

    if ((pData == NULL) || (Size == 0U) ||
        (ReadAddr >= MEMORY_FLASH_SIZE) ||
        (Size > (MEMORY_FLASH_SIZE - ReadAddr)))
    {
        return HAL_ERROR;
    }

    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = QUAD_OUT_FAST_READ_CMD; /* 0x6B */
    sCommand.AddressMode       = QSPI_ADDRESS_1_LINE;
    sCommand.AddressSize       = QSPI_ADDRESS_24_BITS;
    sCommand.Address           = ReadAddr;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_4_LINES;
    sCommand.DummyCycles       = DUMMY_CLOCK_CYCLES_READ_QUAD; /* 8 */
    sCommand.NbData            = Size;
    sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(&hqspi, &sCommand,
                         HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }

    if (HAL_QSPI_Receive(&hqspi, pData,
                         HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}



uint8_t QSPI_AutoPollingMemReady(uint32_t timeout_ms)
{
    QSPI_CommandTypeDef sCommand = {0};
    QSPI_AutoPollingTypeDef sConfig = {0};

    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = READ_STATUS_REG_CMD; /* 0x05 */
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_1_LINE;
    sCommand.DummyCycles       = 0;
    sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    sConfig.Match           = 0x00;
    sConfig.Mask            = 0x01; /* Wait for WIP = 0 */
    sConfig.MatchMode       = QSPI_MATCH_MODE_AND;
    sConfig.StatusBytesSize = 1;
    sConfig.Interval        = 0x10;
    sConfig.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;

    if (HAL_QSPI_AutoPolling(&hqspi, &sCommand, &sConfig, timeout_ms)
        != HAL_OK)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

uint8_t CSP_QSPI_ReadStatusRegister(uint8_t command, uint8_t *status)
{
    QSPI_CommandTypeDef sCommand = {0};

    if ((command != READ_STATUS_REG_CMD) &&
        (command != READ_STATUS_REG2_CMD) &&
        (command != READ_STATUS_REG3_CMD))
    {
        return HAL_ERROR;
    }

    if (status == NULL)
    {
        return HAL_ERROR;
    }

    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = command;
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_1_LINE;
    sCommand.NbData            = 1;
    sCommand.DummyCycles       = 0;
    sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
    sCommand.DdrHoldHalfCycle  = QSPI_DDR_HHC_ANALOG_DELAY;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(&hqspi, &sCommand,
                         HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }

    if (HAL_QSPI_Receive(&hqspi, status,
                         HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}
