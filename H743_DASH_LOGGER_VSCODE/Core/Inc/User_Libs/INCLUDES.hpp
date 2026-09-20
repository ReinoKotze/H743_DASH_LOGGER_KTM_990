#ifndef INCLUDES_HPP
#define INCLUDES_HPP

#include "main.h"
#include "w25q128.h"
#include "User_Libs/st7365_3.5Inch.h"
#include "User_Libs/bsp_sdram.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "User_Libs/LVGL_LCD_LINK.h"
#include "ui.h"
#include "ALTmain.hpp"
#include "SDRAM_ADD_MANIGMENT.h"
#include "lvgl.h"
#include "dma.h"
#include "tim.h"
#include "i2c.h"
#include "quadspi.h"
#include "interrupts.h"

// C++ interfaces are only available to .cpp files.
#ifdef __cplusplus
#include "Buttons.hpp"
#include "ADS1115.hpp"
#include "MCP2518FD.hpp"
#endif

#endif
