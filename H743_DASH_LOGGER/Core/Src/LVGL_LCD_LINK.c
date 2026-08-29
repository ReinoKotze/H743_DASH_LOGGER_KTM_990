/**
 * @file lv_port_disp_template.c
 *
 */

/*Copy this file as "lv_port_disp.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "LVGL_LCD_LINK.h"
#include <stdbool.h>
#include "main.h"
#include "st7365_3.5Inch.h"

/*********************
 *      DEFINES
 *********************/

#define MY_DISP_HOR_RES    320
#define MY_DISP_VER_RES    480


#define BYTES_PER_PIXEL  2
#define LVGL_BUFFER_SIZE  ( MY_DISP_HOR_RES * MY_DISP_VER_RES * BYTES_PER_PIXEL)

#define LVGL_BUF1_ADDRESS   0xC0500000U // LV_HEAP_ADD+(320*480*2)  2 bytes per pixel
#define LVGL_BUF2_ADDRESS   (LVGL_BUF1_ADDRESS + LVGL_BUFFER_SIZE) // LVGL_BUF1_ADDRESS +(320*480*2)  2 bytes per pixel

#define BYTE_PER_PIXEL (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB565)) /*will be 2 for RGB565 */


static bool te_wait_done = false;
//static volatile bool disp_flush_enabled = true;


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
	  disp_init();

	    lv_display_t *disp =lv_display_create(MY_DISP_HOR_RES, MY_DISP_VER_RES);

	    lv_display_set_color_format(disp, LV_COLOR_FORMAT_RGB565);
	    lv_display_set_flush_cb(disp, disp_flush);

	    /*
	     * PARTIAL mode matches LCD_WriteBitmapDMA(): px_map contains
	     * a contiguous buffer holding only the area being flushed.
	     */

	    static uint8_t * const buf1 = (uint8_t *)LVGL_BUF1_ADDRESS;
	    static uint8_t * const buf2 = (uint8_t *)LVGL_BUF2_ADDRESS;

	    lv_display_set_buffers(disp, buf1, buf2, LVGL_BUFFER_SIZE, LV_DISPLAY_RENDER_MODE_PARTIAL);


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
static void disp_flush(lv_display_t * disp_drv, const lv_area_t * area, uint8_t * px_map)
{
    if(disp_flush_enabled) {
        /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one*/



    	if (!te_wait_done) {
    	            (void)LCD_WaitForTE(25U);
    	            te_wait_done = true;
    	        }



    	LCD_WriteBitmapDMA((uint16_t)area->x1,(uint16_t)area->y1,(uint16_t)area->x2,(uint16_t)area->y2,(const uint16_t *)px_map);



    }


    if (lv_display_flush_is_last(disp_drv)) {
         te_wait_done = false;
     }




    /*IMPORTANT!!!
     *Inform the graphics library that you are ready with the flushing*/
    lv_display_flush_ready(disp_drv);
}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
