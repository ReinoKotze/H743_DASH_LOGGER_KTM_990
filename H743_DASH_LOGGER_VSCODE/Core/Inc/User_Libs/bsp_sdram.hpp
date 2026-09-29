#ifndef BSP_SDRAM_HPP
#define BSP_SDRAM_HPP

#include "stm32h7xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Run the memory-device command sequence after MX_FMC_Init(). */
HAL_StatusTypeDef SDRAM_InitSequence(void);

/* Debugger-visible startup diagnostics. */
extern volatile uint32_t sdram_init_stage;
extern volatile uint32_t sdram_init_status;
extern volatile uint32_t sdram_fmc_clock_hz;
extern volatile uint32_t sdram_refresh_count;
extern volatile uint32_t sdram_hal_state;

#ifdef __cplusplus
}
#endif

#endif /* BSP_SDRAM_HPP */
