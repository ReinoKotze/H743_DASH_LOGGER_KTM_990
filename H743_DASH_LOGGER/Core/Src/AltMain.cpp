/*
 * AltMain.c
 *
 *  Created on: 26 Aug 2026
 *      Author: reino
 */
#include "main.h"
#include <string.h>


extern "C" {
#include <string.h>
#include "stdio.h"
#include "w25q128.h"
#include "st7365_3.5Inch.h"
#include "cmsis_os2.h"
#include "gpio.h"

void setup(){
	  CSP_QUADSPI_Init();
	  CSP_QSPI_EnableMemoryMappedMode();
      LCD_Init();

}

void TaskOne(){

HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
Fill(WHITE);
osDelay(200);
Fill(BLACK);
osDelay(200);


}









}




