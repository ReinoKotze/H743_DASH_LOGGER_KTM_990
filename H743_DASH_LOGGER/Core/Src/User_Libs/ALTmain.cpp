/*
 * ALTmain.cpp
 *
 *  Created on: 1 Sept 2026
 *      Author: reino
 */
#include "main.h"
#include <string.h>

#include "User_Libs/w25q128.h"
#include "User_Libs/st7365_3.5Inch.h"
#include "User_Libs/bsp_sdram.h"
#include "stdio.h"
#include <stdbool.h>
#include <string.h>
#include "User_Libs/LVGL_LCD_LINK.h"
#include "ui.h"
#include "ALTmain.hpp"
#include "SDRAM_ADD_MANIGMENT.h"


extern "C" {



void setup()//this is in void main()
{
	  HAL_Delay(5U);
	  CSP_QUADSPI_Init();
	  CSP_QSPI_EnableMemoryMappedMode();
	  SDRAM_InitSequence();
	  LCD_Init();
	  lv_init();
	  lv_tick_set_cb(HAL_GetTick);
	  lv_port_disp_init();
	  ui_init();

}

void tasks()//this is inside loop
{

	  lv_timer_handler();
	  HAL_Delay(5);

}



}







