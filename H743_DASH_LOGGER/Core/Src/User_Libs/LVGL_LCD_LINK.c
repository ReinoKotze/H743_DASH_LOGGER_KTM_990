/**
 * @file lv_port_disp_template.c
 *
 */

/*Copy this file as "lv_port_disp.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "User_Libs/LVGL_LCD_LINK.h"
#include <stdbool.h>
#include "main.h"
#include "User_Libs/st7365_3.5Inch.h"
#include <string.h>
#include "dma2d.h"
/*********************
 *      DEFINES
 *********************/

#define MY_DISP_HOR_RES       320U
#define MY_DISP_VER_RES       480U
#define MY_DISP_ROWS          (MY_DISP_VER_RES/1)
#define BYTE_PER_PIXEL       (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB565))

#define LVGL_DRAW_BUFFER_SIZE (MY_DISP_HOR_RES * MY_DISP_ROWS * BYTE_PER_PIXEL)

//#define LVGL_DRAW_BUFFER_SIZE (MY_DISP_HOR_RES * MY_DISP_VER_RES * BYTE_PER_PIXEL)

#define LVGL_SDRAM_BUF1_ADDRESS  0xC0500000U
#define LVGL_SDRAM_BUF2_ADDRESS  (LVGL_SDRAM_BUF1_ADDRESS + LVGL_DRAW_BUFFER_SIZE)
#define DMA2D_SDRAM_BUF3_ADDRESS (LVGL_SDRAM_BUF2_ADDRESS + (MY_DISP_HOR_RES * MY_DISP_VER_RES * BYTE_PER_PIXEL))
#define DMA2D_SDRAM_BUF3_SIZE    (MY_DISP_HOR_RES * MY_DISP_VER_RES * BYTE_PER_PIXEL)

static bool compose_error = false;

static HAL_StatusTypeDef LCD_DMA2D_CopyArea(const lv_area_t *area, const uint8_t *px_map);
volatile HAL_StatusTypeDef lcd_dma2d_status = HAL_OK;
volatile HAL_StatusTypeDef lcd_mdma_status = HAL_OK;

static uint8_t * const buf_2_1 = (uint8_t *)LVGL_SDRAM_BUF1_ADDRESS;

static uint8_t * const buf_2_2 = (uint8_t *)LVGL_SDRAM_BUF2_ADDRESS;

static uint8_t * const buf3 = (uint8_t *)DMA2D_SDRAM_BUF3_ADDRESS;

//static bool te_wait_done = false;

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init(void);

static void disp_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_disp_init(void)
{
	lv_display_t *disp;
    disp_init();
    memset(buf_2_1, 0, LVGL_DRAW_BUFFER_SIZE);
    memset(buf_2_2, 0, LVGL_DRAW_BUFFER_SIZE);
    memset(buf3, 0, DMA2D_SDRAM_BUF3_SIZE );

    disp = lv_display_create(MY_DISP_HOR_RES, MY_DISP_VER_RES);
    lv_display_set_color_format(disp, LV_COLOR_FORMAT_RGB565);

    lv_display_set_buffers(disp, buf_2_1, buf_2_2, LVGL_DRAW_BUFFER_SIZE, LV_DISPLAY_RENDER_MODE_PARTIAL);


    lv_display_set_flush_cb(disp, disp_flush);



}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*Initialize your display and the required peripherals.*/
static void disp_init(void)
{
	//LCD_Init();
}

volatile bool disp_flush_enabled = true;


/* Enable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_enable_update(void)
{
    disp_flush_enabled = true;
}

/* Disable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_disable_update(void)
{
    disp_flush_enabled = false;
}

/*Flush the content of the internal buffer the specific area on the display.
 *`px_map` contains the rendered image as raw pixel map and it should be copied to `area` on the display.
 *You can use DMA or any hardware acceleration to do this operation in the background but
 *'lv_display_flush_ready()' has to be called when it's finished.*/


static HAL_StatusTypeDef LCD_DMA2D_CopyArea(const lv_area_t *area, const uint8_t *px_map)
{
    uint32_t width;
    uint32_t height;
    uint16_t *destination;
    HAL_StatusTypeDef status;

    if((area == NULL) || (px_map == NULL) ||
       (area->x1 < 0) || (area->y1 < 0) ||
       (area->x2 >= (int32_t)MY_DISP_HOR_RES) ||
       (area->y2 >= (int32_t)MY_DISP_VER_RES) ||
       (area->x2 < area->x1) || (area->y2 < area->y1)) {
        return HAL_ERROR;
    }

    width  = (uint32_t)(area->x2 - area->x1 + 1);
    height = (uint32_t)(area->y2 - area->y1 + 1);

    destination = (uint16_t *)buf3 +
                  ((uint32_t)area->y1 * MY_DISP_HOR_RES) +
                  (uint32_t)area->x1;

    /*
     * Source is a contiguous LVGL partial bitmap.
     * Destination is a 320-pixel-wide full-screen framebuffer.
     */
    hdma2d.Init.OutputOffset = MY_DISP_HOR_RES - width;
    hdma2d.LayerCfg[1].InputOffset = 0U;

    status = HAL_DMA2D_Init(&hdma2d);
    if(status != HAL_OK) {
        return status;
    }

    status = HAL_DMA2D_ConfigLayer(&hdma2d, 1U);
    if(status != HAL_OK) {
        return status;
    }

    status = HAL_DMA2D_Start(&hdma2d,
                             (uint32_t)px_map,
                             (uint32_t)destination,
                             width,
                             height);
    if(status != HAL_OK) {
        return status;
    }

    return HAL_DMA2D_PollForTransfer(&hdma2d, 100U);
}




static void disp_flush(lv_display_t *disp_drv,const lv_area_t *area,uint8_t *px_map)
{



/*this is the DMA2D finction 3rd buffer use. the DMA2D
 * writes to the 3rd buffer then MDMA writes that full
 * display 3rd buffer to the display.
 *
 */
//    if(disp_flush_enabled) {
//        /*
//         * Merge the rendered LVGL partial area into the full buffer 3.
//         */
//        lcd_dma2d_status = LCD_DMA2D_CopyArea(area, px_map);
//
//        if(lcd_dma2d_status != HAL_OK) {
//            compose_error = true;
//        }
//    }
//
//    /*
//     * After LVGL has provided the final area, buffer 3 contains the
//     * complete new display image. Send it once to LCD GRAM.
//     */
//    if(lv_display_flush_is_last(disp_drv)) {
//        if(disp_flush_enabled && !compose_error) {
//            lcd_mdma_status =
//                LCD_WriteBitmapDMA(0U,
//                                   0U,
//                                   MY_DISP_HOR_RES - 1U,
//                                   MY_DISP_VER_RES - 1U,
//                                   (const uint16_t *)buf3);
//        }
//
//        compose_error = false;
//    }
//
//    lv_display_flush_ready(disp_drv);






    if(disp_flush_enabled)
    {
    LCD_WriteBitmapDMA((uint16_t)area->x1,(uint16_t)area->y1,(uint16_t)area->x2,(uint16_t)area->y2,(const uint16_t *)px_map);
    }

    lv_display_flush_ready(disp_drv);

}


#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
