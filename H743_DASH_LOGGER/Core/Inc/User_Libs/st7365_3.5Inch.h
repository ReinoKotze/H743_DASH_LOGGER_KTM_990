/*
 * st7365_3.5Inch.h
 *
 *  Created on: 26 Aug 2026
 *      Author: reino
 */

#ifndef INC_ST7365_3_5INCH_H_
#define INC_ST7365_3_5INCH_H_
#include "main.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LCD_MDMA_MAX_BYTES  (32768U)//(LCD_WIDTH * sizeof(uint16_t))
//#define LCD_MDMA_MAX_BYTES  (65534U) /* Even number: RGB565 pixels */
#define FMC_BANK1_REG  *(volatile uint16_t *)((uint32_t)0x60000000)  // Register Address for A0
#define FMC_BANK1_DATA *(volatile uint16_t *)((uint32_t)0x60000002) // Data Address for A0 -> A0<<1 -> 0010




//functions
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void LCD_WaitForTE(uint32_t timeout_ms);
void delay(uint32_t time);
void LCD_IO_WriteReg(uint16_t Reg);
void LCD_IO_WriteData(uint16_t RegValue);
void hardRst();
void LCD_Init();
void LCD_SetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void LCD_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void LCD_DrawRecFill(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
void Fill(uint16_t color);
void LCD_DrawBitmap(uint16_t x,uint16_t y, const uint16_t *pbmp);
void LCD_WriteBitmap(uint16_t x0, uint16_t y0,uint16_t x1, uint16_t y1, const uint16_t *pixels);
HAL_StatusTypeDef LCD_WriteBitmapDMA(uint16_t x0, uint16_t y0,uint16_t x1, uint16_t y1,const uint16_t *pixels);
void LCD_CleanDCacheForMDMA(const void *address, uint32_t size);
HAL_StatusTypeDef LCD_DMA2_Init(void);
HAL_StatusTypeDef LCD_WriteBitmapDMA2(uint16_t x0, uint16_t y0,uint16_t x1, uint16_t y1,const uint16_t *pixels);
HAL_StatusTypeDef LCD_WriteBitmapDMA2Strided(uint16_t x0, uint16_t y0,uint16_t x1, uint16_t y1,const uint16_t *framebuffer,uint32_t source_stride_pixels);
void LCD_TE_BeginWait(uint32_t timeout_ms);
bool LCD_TE_IsReady(void);
HAL_StatusTypeDef LCD_StartBitmapMDMA_IT(uint16_t x0, uint16_t y0,uint16_t x1, uint16_t y1, const uint16_t *pixels);


//command list
#define swReset 0x01
#define sleepOut 0x11
#define commandSetcont 0xf0
#define memoryAccesscont 0x36
#define dispPixelformat 0x3a
#define interfaceModecont 0xb0
#define frameRate 0xb1
#define dispInversioncont 0xb4
#define blankingporch 0xb5
#define blankingporchcont 0xb6
#define entryModeset 0xb7
#define pwrCont1 0xc0
#define pwrCont2 0xc1
#define pwrCont3 0xc2
#define vcomCont 0xc5
#define posGammacont 0xe0
#define negGammacont 0xe1
#define pwrCont1 0xc0
#define pwrOn 0x29
#define columnAddressSet 0x2a
#define rowAddressSet 0x2b
#define memoryWrite 0x2c
#define tearingEffect 0x35
#define tearingEffectOff 0x34
#define DispNormModeOn 0x13
#define displayOff  0x28

#define LCD_WIDTH   320U
#define LCD_HEIGHT  480U

#define BLACK       0x0000
#define WHITE       0xFFFF
#define RED         0xF800
#define GREEN       0x07E0
#define BLUE        0x001F
#define YELLOW      0xFFE0
#define CYAN        0x07FF
#define MAGENTA     0xF81F
#define GRAY        0x8410
#define ORANGE      0xFC00




#ifdef __cplusplus
}
#endif

#endif /* INC_W25Q128_H_ */
