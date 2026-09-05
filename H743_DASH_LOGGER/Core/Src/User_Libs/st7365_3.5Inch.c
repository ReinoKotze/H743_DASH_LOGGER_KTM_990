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
#include "User_Libs/LVGL_LCD_LINK.h"
#include "tim.h"


extern MDMA_HandleTypeDef hmdma_mdma_channel0_sw_0;
static uint32_t te_wait_start_ms;
static uint32_t te_wait_timeout_ms;
static uint8_t te_wait_active = 0U;

extern volatile uint8_t TEFLAG ;

void LCD_TE_BeginWait(uint32_t timeout_ms)
{
    uint32_t primask = __get_PRIMASK();

    __disable_irq();

    TEFLAG = 0U;
    te_wait_start_ms = HAL_GetTick();
    te_wait_timeout_ms = timeout_ms;
    te_wait_active = 1U;

    __set_PRIMASK(primask);
}

bool LCD_TE_IsReady(void)
{
//    if (te_wait_active == 0U)
//    {
//        return true;
//    }

    if (TEFLAG != 0U)
    {
        te_wait_active = 0U;
        return true;
    }

    if ((uint32_t)(HAL_GetTick() - te_wait_start_ms) >=
        te_wait_timeout_ms)
    {
        te_wait_active = 0U;
        return true; /* Timeout: proceed without TE. */
    }

    return false;
}

void LCD_WaitForTE(uint32_t timeout_ms)
{

	/*for TE pin interrup
	 * PD3 is configured as EXTI3 and named TE_LCD
	 *
	 * The rising-edge callback signals TEFLAG.
	 *
	 *
	 *
	 *
	 * */

	uint32_t start_tick = HAL_GetTick();
	TEFLAG=0U;
	 //__DMB();

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
	    LCD_IO_WriteData(0x48U);// 48 40





//	    LCD_IO_WriteReg(columnAddressSet);
//	    LCD_IO_WriteData(0x00U);
//	    LCD_IO_WriteData(0x00U);
//	    LCD_IO_WriteData(0x01U);
//	    LCD_IO_WriteData(0x3FU);
//
//	    LCD_IO_WriteReg(rowAddressSet);
//	    LCD_IO_WriteData(0x00U);
//	    LCD_IO_WriteData(0x00U);
//	    LCD_IO_WriteData(0x01U);
//	    LCD_IO_WriteData(0xDFU);

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


	   // LCD_IO_WriteReg(tearingEffectOff);


	    LCD_IO_WriteReg(DispNormModeOn);
	    //LCD_IO_WriteReg(0x20U); //invert off
	    LCD_IO_WriteReg(0x21U);  //invert on
	    LCD_IO_WriteReg(pwrOn); /* Display ON */
	    LCD_IO_WriteReg(0x38U);
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
     * Clean cacheable source memory, including the internal D2 draw buffers.
     * MDMA reads physical memory, not the CPU D-cache.
     */
    uint32_t start = (uint32_t)address & ~31UL;
    uint32_t end   = ((uint32_t)address + size + 31UL) & ~31UL;

    SCB_CleanDCache_by_Addr((uint32_t *)start, (int32_t)(end - start));
}








typedef struct
{
    const uint16_t *source;
    uint32_t bytes_remaining;
    uint32_t current_chunk_bytes;

    volatile bool busy;
    volatile HAL_StatusTypeDef status;
} lcd_mdma_transfer_t;

static lcd_mdma_transfer_t lcd_mdma_transfer = {
    .source = NULL,
    .bytes_remaining = 0U,
    .current_chunk_bytes = 0U,
    .busy = false,
    .status = HAL_OK
};

static HAL_StatusTypeDef LCD_MDMA_StartNextChunk(void);

static void LCD_MDMA_FinishFromISR(bool success)
{
    lcd_mdma_transfer.busy = false;
    if(!success && lcd_mdma_transfer.status == HAL_OK)
        lcd_mdma_transfer.status = HAL_ERROR;
    __DSB();
    lv_port_disp_mdma_complete_isr(success);
}
static void LCD_MDMA_ChunkCompleteCallback(MDMA_HandleTypeDef *hmdma)
{
    HAL_StatusTypeDef status;

    if(hmdma != &hmdma_mdma_channel0_sw_0) {
        return;
    }

    if(!lcd_mdma_transfer.busy) {
        return;
    }

    lcd_mdma_transfer.source +=
        lcd_mdma_transfer.current_chunk_bytes / sizeof(uint16_t);

    lcd_mdma_transfer.bytes_remaining -=
        lcd_mdma_transfer.current_chunk_bytes;

    if(lcd_mdma_transfer.bytes_remaining == 0U) {
        lcd_mdma_transfer.status = HAL_OK;
        LCD_MDMA_FinishFromISR(true);
        return;
    }

    /*
     * HAL_MDMA_IRQHandler has already changed the channel state to READY
     * before it calls this callback, so the next chunk can start here.
     */
    status = LCD_MDMA_StartNextChunk();

    if(status != HAL_OK) {
        lcd_mdma_transfer.status = status;
        LCD_MDMA_FinishFromISR(false);
    }
}

static void LCD_MDMA_ErrorCallback(MDMA_HandleTypeDef *hmdma)
{
    if(hmdma != &hmdma_mdma_channel0_sw_0) {
        return;
    }

    lcd_mdma_transfer.status = HAL_ERROR;
    LCD_MDMA_FinishFromISR(false);
}

static HAL_StatusTypeDef LCD_MDMA_StartNextChunk(void)
{
    HAL_StatusTypeDef status;

    if(lcd_mdma_transfer.bytes_remaining == 0U) {
        return HAL_ERROR;
    }

    lcd_mdma_transfer.current_chunk_bytes =
        lcd_mdma_transfer.bytes_remaining;

    if(lcd_mdma_transfer.current_chunk_bytes > LCD_MDMA_MAX_BYTES) {
        lcd_mdma_transfer.current_chunk_bytes = LCD_MDMA_MAX_BYTES;
    }

    status = HAL_MDMA_Start_IT(
        &hmdma_mdma_channel0_sw_0,
        (uint32_t)lcd_mdma_transfer.source,
        (uint32_t)&FMC_BANK1_DATA,
        lcd_mdma_transfer.current_chunk_bytes,
        1U
    );

    return status;
}

HAL_StatusTypeDef LCD_StartBitmapMDMA_IT(uint16_t x0, uint16_t y0,
                                         uint16_t x1, uint16_t y1,
                                         const uint16_t *pixels)
{
    uint32_t byte_count;
    HAL_StatusTypeDef status;

    if((pixels == NULL) ||
       (x1 < x0) || (y1 < y0) ||
       (x1 >= LCD_WIDTH) || (y1 >= LCD_HEIGHT) ||
       lcd_mdma_transfer.busy) {
        return HAL_ERROR;
    }

    byte_count = (uint32_t)(x1 - x0 + 1U) *
                 (uint32_t)(y1 - y0 + 1U) *
                 sizeof(uint16_t);

    LCD_CleanDCacheForMDMA(pixels, byte_count);

    LCD_SetWindow(x0, y0, x1, y1);
    LCD_IO_WriteReg(memoryWrite);
    __DSB();

    lcd_mdma_transfer.source = pixels;
    lcd_mdma_transfer.bytes_remaining = byte_count;
    lcd_mdma_transfer.current_chunk_bytes = 0U;
    lcd_mdma_transfer.status = HAL_OK;
    lcd_mdma_transfer.busy = true;

    hmdma_mdma_channel0_sw_0.XferCpltCallback =
        LCD_MDMA_ChunkCompleteCallback;

    hmdma_mdma_channel0_sw_0.XferErrorCallback =
        LCD_MDMA_ErrorCallback;

    status = LCD_MDMA_StartNextChunk();

    if(status != HAL_OK) {
        lcd_mdma_transfer.busy = false;
        lcd_mdma_transfer.status = status;
    }

    return status;
}














HAL_StatusTypeDef LCD_WriteBitmapDMA(uint16_t x0, uint16_t y0,
                                     uint16_t x1, uint16_t y1,
                                     const uint16_t *pixels)
{
	uint32_t bytes_remaining;
	    uint32_t chunk_bytes;
	    HAL_StatusTypeDef status;

	    if((pixels == NULL) ||
	       (x1 < x0) || (y1 < y0) ||
	       (x1 >= LCD_WIDTH) || (y1 >= LCD_HEIGHT)) {
	        return HAL_ERROR;
	    }

	    LCD_SetWindow(x0, y0, x1, y1);
	    LCD_IO_WriteReg(memoryWrite);

	    bytes_remaining = (uint32_t)(x1 - x0 + 1U) *
	                      (uint32_t)(y1 - y0 + 1U) *
	                      sizeof(uint16_t);

	    LCD_CleanDCacheForMDMA(pixels, bytes_remaining);
	    __DSB();

	    while(bytes_remaining != 0U) {
	        chunk_bytes = bytes_remaining;

	        if(chunk_bytes > LCD_MDMA_MAX_BYTES) {
	            chunk_bytes = LCD_MDMA_MAX_BYTES;
	        }

	        status = HAL_MDMA_Start(&hmdma_mdma_channel0_sw_0,
	                                (uint32_t)pixels,
	                                (uint32_t)&FMC_BANK1_DATA,
	                                chunk_bytes,
	                                1U);

	        if(status != HAL_OK) {
	            return status;
	        }

	        status = HAL_MDMA_PollForTransfer(&hmdma_mdma_channel0_sw_0,
	                                          HAL_MDMA_FULL_TRANSFER,
	                                          100U);

	        if(status != HAL_OK) {
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
    if((pixels == NULL) || (x1 < x0) || (y1 < y0) ||
       (x1 >= LCD_WIDTH) || (y1 >= LCD_HEIGHT)) {
        return HAL_ERROR;
    }

    uint32_t remaining = (uint32_t)(x1 - x0 + 1U) *
                         (uint32_t)(y1 - y0 + 1U);
    LCD_CleanDCacheForMDMA(pixels, remaining * sizeof(uint16_t));
    LCD_SetWindow(x0, y0, x1, y1);
    LCD_IO_WriteReg(memoryWrite);

    while(remaining != 0U) {
        uint32_t count = (remaining > 65535U) ? 65535U : remaining;
        HAL_StatusTypeDef status = HAL_DMA_Start(
            &hdma_memtomem_dma2_stream0, (uint32_t)pixels,
            (uint32_t)&FMC_BANK1_DATA, count);

        if(status == HAL_OK) {
            status = HAL_DMA_PollForTransfer(&hdma_memtomem_dma2_stream0,
                                             HAL_DMA_FULL_TRANSFER, 100U);
        }
        if(status != HAL_OK) {
            /* Poll may already have attempted an abort. Check hardware too:
               never release an LVGL buffer while DMA can still read it. */
            if(HAL_DMA_GetState(&hdma_memtomem_dma2_stream0) == HAL_DMA_STATE_BUSY) {
                (void)HAL_DMA_Abort(&hdma_memtomem_dma2_stream0);
            }
            if((DMA2_Stream0->CR & DMA_SxCR_EN) != 0U) {
                Error_Handler();
                while(1) {}
            }
            __DSB();
            /* Restart the entire window: the failed chunk may be partial.
               Source buffer is still owned by this blocking flush. */
            const uint16_t *retry = pixels -
                ((uint32_t)(x1 - x0 + 1U) * (y1 - y0 + 1U) - remaining);
            uint32_t total = (uint32_t)(x1 - x0 + 1U) * (y1 - y0 + 1U);
            LCD_SetWindow(x0, y0, x1, y1);
            LCD_IO_WriteReg(memoryWrite);
            while(total-- != 0U) {
                FMC_BANK1_DATA = *retry++;
            }
            __DSB();
            return HAL_OK;
        }
        pixels += count;
        remaining -= count;
    }

    __DSB();
    return HAL_OK;
}
void HAL_GPIO_EXTI_Callback(uint16_t pin)
{
    if(pin == TE_LCD_Pin) {
        lv_port_disp_te_isr();
    }
}