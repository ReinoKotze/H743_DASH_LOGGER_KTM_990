/*
 * w25q128.h
 *
 *  Created on: 26 Aug 2026
 *      Author: reino
 */

#ifndef INC_W25Q128_H_
#define INC_W25Q128_H_

#include "main.h"



/* USER CODE BEGIN Private defines */
uint8_t CSP_QUADSPI_Init(void);
uint8_t CSP_QSPI_EraseSector(uint32_t EraseStartAddress ,uint32_t EraseEndAddress);
uint8_t CSP_QSPI_EraseBlock(uint32_t flash_address);
uint8_t CSP_QSPI_WriteMemory(uint8_t* buffer, uint32_t address, uint32_t buffer_size);
uint8_t CSP_QSPI_EnableMemoryMappedMode(void);
uint8_t CSP_QSPI_Erase_Chip (void);
uint8_t QSPI_AutoPollingMemReady(uint32_t timeout_ms);
uint8_t CSP_QSPI_Read(uint8_t* pData, uint32_t ReadAddr, uint32_t Size);
uint8_t QSPI_AutoPollingMemReady(uint32_t timeout_ms);
uint8_t CSP_QSPI_ReadStatusRegister(uint8_t command, uint8_t *status);


/*W25Q128 memory parameters*/
#define MEMORY_FLASH_SIZE				0x1000000  /* 128Mbit =>16Mbyte */
#define MEMORY_BLOCK_SIZE				0x10000   /*  blocks of 64KBytes */
#define MEMORY_SECTOR_SIZE				0x1000    /* 4kBytes */
#define MEMORY_PAGE_SIZE				0x100     /* 256 bytes */


/*W25Q128 commands */
#define CHIP_ERASE_CMD 0xC7
#define READ_STATUS_REG_CMD 0x05
#define WRITE_ENABLE_CMD 0x06
#define VOLATILE_SR_WRITE_ENABLE             0x50
#define READ_STATUS_REG2_CMD 0x35
#define WRITE_STATUS_REG2_CMD 0x31
#define READ_STATUS_REG3_CMD 0x15
#define WRITE_STATUS_REG3_CMD                0x11
#define SECTOR_ERASE_CMD 0x20
#define BLOCK_ERASE_CMD 0xD8
#define QUAD_IN_FAST_PROG_CMD 0x32
#define FAST_PROG_CMD 0x02
#define QUAD_OUT_FAST_READ_CMD 0x6B
#define DUMMY_CLOCK_CYCLES_READ_QUAD 8
#define QUAD_IN_OUT_FAST_READ_CMD 0xEB
#define RESET_ENABLE_CMD 0x66
#define RESET_EXECUTE_CMD 0x99

#define W25Q128_READY_TIMEOUT_MS       5000U
#define W25Q128_CHIP_ERASE_TIMEOUT_MS  210000U



#endif /* INC_W25Q128_H_ */
