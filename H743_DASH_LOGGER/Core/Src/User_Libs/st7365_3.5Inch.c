/*
 * st7365_3.5Inch.c
 *
 *  Created on: 26 Aug 2026
 *      Author: reino
 */
#include "User_Libs/st7365_3.5Inch.h"


#include "main.h"
#include "dma.h"
#include <stdbool.h>
#include <string.h>

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

	/*for TE pin interrup
	 * PIN PD3 set as GPIO_EXTI3 and named TE_LCD
	 *
	 * EXTI line 3 is enabled in the NVIC.
	 *
	 *
	 *
	 *
	 * */

	uint32_t start_tick = HAL_GetTick();
	TEFLAG=0U;
	 __DMB();

	    while ((TEFLAG == 0U) &&
	           ((HAL_GetTick() - start_tick) < timeout_ms)) {
	    }
}


void delay(uint32_t time)
{

HAL_Delay(time);

}

void LCD_IO_WriteReg(uint16_t Reg)
{
	FMC_BANK1_REG = Reg;

	//__DSB();

}

void LCD_IO_WriteData(uint16_t RegValue)
{
	FMC_BANK1_DATA = RegValue;

	//__DSB();

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

	    LCD_IO_WriteReg(sleepOut);
	    delay(120U);

	    /*
	     * Keep panel output disabled while controller registers and GRAM
	     * are initialized. GRAM contents after power-up are undefined.
	     */
	    LCD_IO_WriteReg(displayOff);

	    LCD_IO_WriteReg(dispPixelformat);
	    LCD_IO_WriteData(0x55U); /* RGB565 */

	    LCD_IO_WriteReg(memoryAccesscont);
	    LCD_IO_WriteData(0x48U);

	    LCD_IO_WriteReg(columnAddressSet);
	    LCD_IO_WriteData(0x00U);
	    LCD_IO_WriteData(0x00U);
	    LCD_IO_WriteData(0x01U);
	    LCD_IO_WriteData(0x3FU);

	    LCD_IO_WriteReg(rowAddressSet);
	    LCD_IO_WriteData(0x00U);
	    LCD_IO_WriteData(0x00U);
	    LCD_IO_WriteData(0x01U);
	    LCD_IO_WriteData(0xDFU);

	    /*
	     * Clear all 320 x 480 RGB565 pixels to black before enabling
	     * the panel output.
	     */
	    Fill(BLACK);

	    /*
	     * TE mode 1: vertical blanking only.
	     */
	    LCD_IO_WriteReg(tearingEffect);
	    LCD_IO_WriteData(0x00U);

	    LCD_IO_WriteReg(DispNormModeOn);
	    LCD_IO_WriteReg(pwrOn); /* Display ON */

	    delay(20U);
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
    uint32_t pixel_count;

    if((pixels == NULL) ||
       (x1 < x0) || (y1 < y0) ||
       (x1 >= LCD_WIDTH) || (y1 >= LCD_HEIGHT)) {
        return;
    }

    pixel_count = (uint32_t)(x1 - x0 + 1U) *
                  (uint32_t)(y1 - y0 + 1U);

    /*
     * Begin the LCD update at vertical blanking. This prevents the panel from
     * scanning the spinner area while its old and new pixels are mixed.
     */
    LCD_WaitForTE(25U);

    LCD_SetWindow(x0, y0, x1, y1);
    LCD_IO_WriteReg(memoryWrite);

    while(pixel_count-- != 0U) {
        FMC_BANK1_DATA = *pixels++;
    }

    __DSB();
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
	        (x1 >= LCD_WIDTH) || (y1 >= LCD_HEIGHT)) {
	        return HAL_ERROR;
	    }

	    /*
	     * TE synchronization occurs once in the LVGL flush callback.
	     * Do not wait for TE in this function.
	     */
	    LCD_SetWindow(x0, y0, x1, y1);
	    LCD_IO_WriteReg(memoryWrite);

	    bytes_remaining = (uint32_t)(x1 - x0 + 1U) *
	                      (uint32_t)(y1 - y0 + 1U) *
	                      sizeof(uint16_t);

	    /*
	     * Your SDRAM is currently MPU non-cacheable, so this is not required.
	     * It is harmless and makes the function safe if SDRAM becomes cacheable.
	     */
	    LCD_CleanDCacheForMDMA(pixels, bytes_remaining);

	    while (bytes_remaining != 0U) {

	        /*
	         * Limit each transfer to one display line, or the remaining tail.
	         */
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

HAL_StatusTypeDef LCD_WriteBitmapDMA2(uint16_t x0, uint16_t y0,
                                      uint16_t x1, uint16_t y1,
                                      const uint16_t *pixels)
{
	 uint32_t pixels_remaining;
	    uint32_t chunk_pixels;
	   uint32_t byte_count;                 /* Remove the // */
	    HAL_StatusTypeDef status;

	    if((pixels == NULL) ||
	       (x1 < x0) || (y1 < y0) ||
	       (x1 >= LCD_WIDTH) || (y1 >= LCD_HEIGHT)) {
	        return HAL_ERROR;
	    }

	    pixels_remaining = (uint32_t)(x1 - x0 + 1U) *
	                       (uint32_t)(y1 - y0 + 1U);

	    byte_count = pixels_remaining * sizeof(uint16_t);  /* Add this */

	   LCD_CleanDCacheForMDMA(pixels, byte_count);        /* Remove the // */
	  //  __DSB();
	   __NOP();
	    LCD_SetWindow(x0, y0, x1, y1);
	    LCD_IO_WriteReg(memoryWrite);
        __NOP();
	    while(pixels_remaining != 0U) {
	        chunk_pixels = (pixels_remaining > 65535U) ?
	                       65535U : pixels_remaining;

	        status = HAL_DMA_Start(&hdma_memtomem_dma2_stream0,
	                               (uint32_t)pixels,
	                               (uint32_t)&FMC_BANK1_DATA,
	                               chunk_pixels);

	        if(status != HAL_OK) {
	            return status;
	        }

	        status = HAL_DMA_PollForTransfer(&hdma_memtomem_dma2_stream0,
	                                         HAL_DMA_FULL_TRANSFER,
	                                         100U);

	        if(status != HAL_OK) {
	            return status;
	        }

	        pixels += chunk_pixels;
	        pixels_remaining -= chunk_pixels;
	    }

	   // __DSB();
	    __NOP();
	    return HAL_OK;
}

HAL_StatusTypeDef LCD_WriteBitmapDMA2Strided(uint16_t x0, uint16_t y0,
                                             uint16_t x1, uint16_t y1,
                                             const uint16_t *framebuffer,
                                             uint32_t source_stride_pixels)
{
    uint32_t width;
    uint32_t height;
    uint32_t row;
    uint32_t source_span_bytes;
    const uint16_t *source_line;
    HAL_StatusTypeDef status;

    if((framebuffer == NULL) ||
       (source_stride_pixels < LCD_WIDTH) ||
       (x1 < x0) || (y1 < y0) ||
       (x1 >= LCD_WIDTH) || (y1 >= LCD_HEIGHT)) {
        return HAL_ERROR;
    }

    width  = (uint32_t)x1 - (uint32_t)x0 + 1U;
    height = (uint32_t)y1 - (uint32_t)y0 + 1U;

    /*
     * LVGL DIRECT mode passes the start of the complete framebuffer.
     * Clean the full memory range DMA will read.
     */
    source_span_bytes =
        (((height - 1U) * source_stride_pixels) + width) * sizeof(uint16_t);

    LCD_CleanDCacheForMDMA(framebuffer, source_span_bytes);
    __DSB();

    LCD_SetWindow(x0, y0, x1, y1);
    LCD_IO_WriteReg(memoryWrite);

    for(row = 0U; row < height; row++) {
        source_line = framebuffer +
                      (((uint32_t)y0 + row) * source_stride_pixels) +
                      (uint32_t)x0;

        status = HAL_DMA_Start(&hdma_memtomem_dma2_stream0,
                               (uint32_t)source_line,
                               (uint32_t)&FMC_BANK1_DATA,
                               width);

        if(status != HAL_OK) {
            return status;
        }

        status = HAL_DMA_PollForTransfer(&hdma_memtomem_dma2_stream0,
                                         HAL_DMA_FULL_TRANSFER,
                                         100U);

        if(status != HAL_OK) {
            return status;
        }
    }

    __DSB();
    return HAL_OK;
}
