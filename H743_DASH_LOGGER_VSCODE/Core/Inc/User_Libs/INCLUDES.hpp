#ifndef INCLUDES_HPP
#define INCLUDES_HPP

#include "main.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "ui.h" //squareline studio file
#include "lvgl.h"

//HAL file includes 
#include "dma.h"
#include "tim.h"
#include "i2c.h"
#include "quadspi.h"

// C++ interfaces are only available to .cpp files.
#ifdef __cplusplus
#include "Buttons.hpp"
#include "ADS1115.hpp"
#include "MCP2518FD.hpp"
#include "interrupts.hpp"
#include "ALTmain.hpp"
#include "SDRAM_ADD_MANIGMENT.hpp"
#include "LVGL_LCD_LINK.hpp"
#include "w25q128.hpp"
#include "st7365_3.5Inch.hpp"
#include "bsp_sdram.hpp"
#endif

#endif
