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
/*********************
 *      DEFINES
 *********************/

#define MY_DISP_HOR_RES       320U
#define MY_DISP_VER_RES       480U
#define MY_DISP_ROWS          (MY_DISP_VER_RES/2)
#define BYTE_PER_PIXEL       (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB565))

#define LVGL_DRAW_BUFFER_SIZE (MY_DISP_HOR_RES * MY_DISP_ROWS * BYTE_PER_PIXEL)

//#define LVGL_DRAW_BUFFER_SIZE (MY_DISP_HOR_RES * MY_DISP_VER_RES * BYTE_PER_PIXEL)

#define LVGL_SDRAM_BUF1_ADDRESS  0xC0500000U
#define LVGL_SDRAM_BUF2_ADDRESS  (LVGL_SDRAM_BUF1_ADDRESS + LVGL_DRAW_BUFFER_SIZE)


static uint8_t * const buf_2_1 = (uint8_t *)LVGL_SDRAM_BUF1_ADDRESS;


static uint8_t * const buf_2_2 = (uint8_t *)LVGL_SDRAM_BUF2_ADDRESS;

static bool te_wait_done = false;

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
static void disp_flush(lv_display_t *disp_drv,const lv_area_t *area,uint8_t *px_map)
{
    if(disp_flush_enabled) {
        /*
         * Synchronize the first LCD transfer in this LVGL refresh
         * to the panel's vertical blanking interval.
         */
        if(!te_wait_done) {
            LCD_WaitForTE(1U);
            te_wait_done = true;
        }

    LCD_WriteBitmapDMA2((uint16_t)area->x1,(uint16_t)area->y1,(uint16_t)area->x2,(uint16_t)area->y2,(const uint16_t *)px_map);
    }

       /*
        * Reset only after the last slice of this LVGL refresh.
        */
       if(lv_display_flush_is_last(disp_drv)) {
           te_wait_done = false;
       }
    lv_display_flush_ready(disp_drv);
}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
