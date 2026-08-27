/*
 * st7365_3.5Inch.c
 *
 *  Created on: 26 Aug 2026
 *      Author: reino
 */
#include "st7365_3.5Inch.h"


#include "main.h"
#include "freertos.h"
#include "cmsis_os2.h"

//int TEFLAG=0;

//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//  /* Prevent unused argument(s) compilation warning */
//  if(GPIO_Pin == TE_LCD_Pin)
//  {
//	  TEFLAG=1;
//  }
//
//  /* NOTE: This function Should not be modified, when the callback is needed,
//           the HAL_GPIO_EXTI_Callback could be implemented in the user file
//   */
//}



void TE_wait(void)
{

//	TEFLAG=0;
//	int32_t timeout = HAL_GetTick() ;   // 50 ms timeout
//
//	    while(TEFLAG == 0)
//	    {
//	        if(HAL_GetTick() > timeout) break;   // safety
//	    }


}




void delay(uint32_t time)
{

HAL_Delay(time);
	//osDelay(time);

}

void LCD_IO_WriteReg(uint16_t Reg)
{
	FMC_BANK1_REG = Reg;

	__DSB();
		__ISB();
}

void LCD_IO_WriteData(uint16_t RegValue)
{
	FMC_BANK1_DATA = RegValue;

	__DSB();
		__ISB();
}




void hardRst()
{
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, 1);
    delay(20);
    HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, 0);
    delay(20);
    HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, 1);
    delay(20);

    LCD_IO_WriteReg(swReset) ;
    delay(120);

}

void LCD_Init()
{
	hardRst();

	    LCD_IO_WriteReg(sleepOut) ;
	    delay(120);

	    //gamma stuff here



	    LCD_IO_WriteReg(dispPixelformat) ;
	    LCD_IO_WriteData(0x55);


	    LCD_IO_WriteReg(memoryAccesscont) ;
	    LCD_IO_WriteData(0x48);

	    LCD_IO_WriteReg(columnAddressSet) ;
	    LCD_IO_WriteData(0x00);
	    LCD_IO_WriteData(0x00);
	    LCD_IO_WriteData(0x01);
	    LCD_IO_WriteData(0x3f);

	    LCD_IO_WriteReg(rowAddressSet) ;
	    LCD_IO_WriteData(0x00);
	    LCD_IO_WriteData(0x00);
	    LCD_IO_WriteData(0x01);
	    LCD_IO_WriteData(0xdf);

	    LCD_IO_WriteReg(0x35) ;//tearing effect
	    LCD_IO_WriteData(0x01);

	    LCD_IO_WriteReg(0x13) ;
	    LCD_IO_WriteReg(pwrOn) ;
}


void LCD_SetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
	TE_wait();
	LCD_IO_WriteReg(columnAddressSet) ;
    LCD_IO_WriteData(x0 >> 8);
    LCD_IO_WriteData(x0 & 0xff);
    LCD_IO_WriteData(x1 >> 8);
    LCD_IO_WriteData(x1 & 0xff);

    LCD_IO_WriteReg(rowAddressSet) ;
    LCD_IO_WriteData(y0 >> 8);
    LCD_IO_WriteData(y0 & 0xff);
    LCD_IO_WriteData(y1 >> 8);
    LCD_IO_WriteData(y1 & 0xff);

}



void LCD_DrawPixel(uint16_t x, uint16_t y, uint16_t color)
{

	LCD_SetWindow(x, y, x, y);
	LCD_IO_WriteReg(memoryWrite);
	LCD_IO_WriteData(color);

}

void LCD_DrawRecFill(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{


	    uint32_t pixels = (uint32_t)(x1 - x0 + 1) * (y1 - y0 + 1);

	    LCD_SetWindow(x0, y0, x1, y1);
	    LCD_IO_WriteReg(memoryWrite);

	        while(pixels--)
	            {
	        	LCD_IO_WriteData(color);          // <-- Use 16-bit write if available
	            }
}


void Fill(uint16_t color)
{
	LCD_IO_WriteReg(columnAddressSet) ;
	    LCD_IO_WriteData(0x00);
	    LCD_IO_WriteData(0x00);
	    LCD_IO_WriteData(0x01);
	    LCD_IO_WriteData(0x3f);

	    LCD_IO_WriteReg(rowAddressSet) ;
	    LCD_IO_WriteData(0x00);
	    LCD_IO_WriteData(0x00);
	    LCD_IO_WriteData(0x01);
	    LCD_IO_WriteData(0xdf);

	    LCD_IO_WriteReg(memoryWrite);
	    for (uint32_t i = 0; i < (320UL * 480UL); i++)
	    LCD_IO_WriteData(color);

}



