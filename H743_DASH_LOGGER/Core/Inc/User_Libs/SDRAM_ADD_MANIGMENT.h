/*
 * SDRAM_ADD_MANIGMENT.h
 *
 *  Created on: 2 Sept 2026
 *      Author: reino
 */

#ifndef INC_USER_LIBS_SDRAM_ADD_MANIGMENT_H_
#define INC_USER_LIBS_SDRAM_ADD_MANIGMENT_H_

/*all files will follow this structure
 *
 * ----size
 *
 * ----address (previous_add + size)
 *
 */

// SDRAM address list
#define SDRAM_START_ADD 0xc0000000U

//lv_conf.h file, #if=1 if external sdram is used for lvgl heap
#if  0

#define LVGL_HEAP_ADD SDRAM_START_ADD // define not used here, seprate define used in lv_conf. 5mb for lvgl heap
#define LVGL_HEAP_SIZE 65536
#define USE_START_ADD (SDRAM_START_ADD+LVGL_HEAP_SIZE)

#else

#define LVGL_HEAP_ADD 0x0 // define not used here, seprate define used in lv_conf. 5mb for lvgl heap
#define LVGL_HEAP_SIZE 65536
#define USE_START_ADD SDRAM_START_ADD

#endif

//LVGL_LCD_LINC.c file
//sizes
#define MY_DISP_HOR_RES       320U
#define MY_DISP_VER_RES       480U
#define MY_DISP_ROWS          (MY_DISP_VER_RES/1)
#define BYTE_PER_PIXEL       (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB565))

#define LVGL_DRAW_BUFFER_SIZE (MY_DISP_HOR_RES * MY_DISP_ROWS * BYTE_PER_PIXEL)
#define LVGL_SDRAM_BUF1_ADDRESS  (USE_START_ADD+LVGL_DRAW_BUFFER_SIZE)
#define LVGL_SDRAM_BUF2_ADDRESS  (LVGL_SDRAM_BUF1_ADDRESS + LVGL_DRAW_BUFFER_SIZE)

#define DMA2D_SDRAM_BUF3_SIZE    (MY_DISP_HOR_RES * MY_DISP_VER_RES * BYTE_PER_PIXEL)
#define DMA2D_SDRAM_BUF3_ADDRESS (LVGL_SDRAM_BUF2_ADDRESS + (MY_DISP_HOR_RES * MY_DISP_VER_RES * BYTE_PER_PIXEL))




#endif /* INC_USER_LIBS_SDRAM_ADD_MANIGMENT_H_ */
