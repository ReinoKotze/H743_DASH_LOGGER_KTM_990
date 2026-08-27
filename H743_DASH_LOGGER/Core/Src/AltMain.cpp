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

void setup(){
	  CSP_QUADSPI_Init();
	  CSP_QSPI_EnableMemoryMappedMode();
      LCD_Init();

}

void TaskOne(){

Fill(WHITE);
osDelay(200);
Fill(BLACK);
osDelay(200);


}









}




