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

extern MDMA_HandleTypeDef hmdma_mdma_channel0_sw_0;


static volatile uint8_t TEFLAG = 0U;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */
  if(GPIO_Pin == TE_LCD_Pin)
  {
	  TEFLAG=1U;
  }

  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_GPIO_EXTI_Callback could be implemented in the user file
   */
}


void LCD_WaitForTE(uint32_t timeout_ms)
{
	uint32_t start = HAL_GetTick();
	TEFLAG=0U;


	 while ((TEFLAG == 0U) && ((HAL_GetTick() - start) < timeout_ms)) {
	    }

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

}

void LCD_IO_WriteData(uint16_t RegValue)
{
	FMC_BANK1_DATA = RegValue;

	__DSB();

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

	    LCD_IO_WriteReg(tearingEffect) ;//tearing effect
	    LCD_IO_WriteData(0x00);

	    LCD_IO_WriteReg(DispNormModeOn) ;
	    LCD_IO_WriteReg(pwrOn) ;
}


void LCD_SetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
	//TE_wait();
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

void LCD_WriteBitmap(uint16_t x0, uint16_t y0,uint16_t x1, uint16_t y1,const uint16_t *pixels)
{
    uint32_t pixel_count=((uint32_t)(x1 - x0 + 1U) * (uint32_t)(y1 - y0 + 1U));

    //(void)LCD_WaitForTE(25U);


    LCD_SetWindow(x0, y0, x1, y1);
    LCD_IO_WriteReg(memoryWrite);
    /*
     * Direct FMC writes: do not use LCD_IO_WriteData() here,
     * because a DSB per pixel is unnecessarily slow.
     */
    while (pixel_count-- != 0U) {
        FMC_BANK1_DATA = *pixels++;
    }

    __DSB();  /* Finish the final FMC transaction. */
}

void LCD_DrawPixel(uint16_t x, uint16_t y, uint16_t color)
{
	(void)LCD_WaitForTE(25U);
	LCD_SetWindow(x, y, x, y);
	LCD_IO_WriteReg(memoryWrite);
	FMC_BANK1_DATA = color;
	    __DSB();

}

void LCD_DrawRecFill(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{


	   uint32_t pixels;

	    if ((x1 < x0) || (y1 < y0)) {
	        return;
	    }
	    (void)LCD_WaitForTE(25U);
	    LCD_SetWindow(x0, y0, x1, y1);
	    LCD_IO_WriteReg(memoryWrite);

	    pixels = ((uint32_t)(x1 - x0 + 1U) *
	              (uint32_t)(y1 - y0 + 1U));

	    while (pixels-- != 0U) {
	        FMC_BANK1_DATA = color;
	    }

	    __DSB();
}


void Fill(uint16_t color)
{
	LCD_DrawRecFill(0U, 0U, LCD_WIDTH - 1U, LCD_HEIGHT - 1U, color);

}

void LCD_CleanDCacheForMDMA(const void *address, uint32_t size)
{
    /*
     * Required only if SDRAM is configured as cacheable.
     * MDMA reads SDRAM, not the CPU D-cache.
     */
    uint32_t start = (uint32_t)address & ~31UL;
    uint32_t end   = ((uint32_t)address + size + 31UL) & ~31UL;

    SCB_CleanDCache_by_Addr((uint32_t *)start, (int32_t)(end - start));
}

HAL_StatusTypeDef LCD_WriteBitmapDMA(uint16_t x0, uint16_t y0,
                                     uint16_t x1, uint16_t y1,
                                     const uint16_t *pixels)
{
    uint32_t bytes_remaining;
    uint32_t chunk_bytes;
    HAL_StatusTypeDef status;

    if ((pixels == NULL) ||
        (x1 < x0) || (y1 < y0) ||
        (x1 >= 320U) || (y1 >= 480U)) {
        return HAL_ERROR;
    }

    (void)LCD_WaitForTE(25U);

    LCD_SetWindow(x0, y0, x1, y1);
    LCD_IO_WriteReg(memoryWrite);

    bytes_remaining = (uint32_t)(x1 - x0 + 1U) *
                      (uint32_t)(y1 - y0 + 1U) *
                      sizeof(uint16_t);

    /* Make LVGL's cacheable SDRAM buffer visible to MDMA. */
    LCD_CleanDCacheForMDMA(pixels, bytes_remaining);

    while (bytes_remaining != 0U) {
        chunk_bytes = (bytes_remaining > LCD_MDMA_MAX_BYTES) ?
                      LCD_MDMA_MAX_BYTES : bytes_remaining;

        status = HAL_MDMA_Start(&hmdma_mdma_channel0_sw_0,
                                (uint32_t)pixels,
                                (uint32_t)&FMC_BANK1_DATA,
                                chunk_bytes,
                                1U);
        if (status != HAL_OK) {
            return status;
        }

        status = HAL_MDMA_PollForTransfer(&hmdma_mdma_channel0_sw_0,
                                          HAL_MDMA_FULL_TRANSFER,
                                          100U);
        if (status != HAL_OK) {
            return status;
        }

        pixels += chunk_bytes / sizeof(uint16_t);
        bytes_remaining -= chunk_bytes;
    }

    __DSB();
    return HAL_OK;
}
