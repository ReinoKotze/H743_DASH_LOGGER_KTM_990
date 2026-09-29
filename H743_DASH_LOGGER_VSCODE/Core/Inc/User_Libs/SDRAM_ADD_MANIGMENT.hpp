/*
 * SDRAM_ADD_MANIGMENT.hpp
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



// 1: LVGL buffers in external SDRAM, with LCD transfers staged through
//    an internal SRAM scanline buffer.
// 0: LVGL buffers in internal RAM_D2 and LCD transfers directly from them.
#if 0
#define USE_EXTERNAL_SDRAM 1
#define SDRAM_START_ADD 0xc0000000U
/* CPU cycles left idle when changing the shared FMC bus between SDRAM reads
   and LCD writes. Increase in small steps if the prototype wiring rings. */
#define LCD_FMC_SETTLE_CYCLES 512U
#define LCD_SDRAM_VERIFY_READS 1
#define LCD_SDRAM_READ_RETRIES 3U
/* Repeat each staged LCD scanline write. The final pass overwrites transient
   corruption from an earlier pass on the long prototype wiring. */
#define LCD_SCANLINE_WRITE_PASSES 1U
#else
#define USE_EXTERNAL_SDRAM 0
#define SDRAM_START_ADD 0x30000000U
#define LCD_FMC_SETTLE_CYCLES 0U
#define LCD_SDRAM_VERIFY_READS 0
#define LCD_SDRAM_READ_RETRIES 0U
#define LCD_SCANLINE_WRITE_PASSES 1U
#endif


//lv_conf.h file, #if=1 if external sdram is used for lvgl heap
#if  0

#define LVGL_HEAP_ADD SDRAM_START_ADD // define not used here, seprate define used in lv_conf. 5mb for lvgl heap
#define LVGL_HEAP_SIZE 65536
#define USE_START_ADD (SDRAM_START_ADD+LVGL_HEAP_SIZE)

#else

#define LVGL_HEAP_ADD 0 // define not used here, seprate define used in lv_conf. 5mb for lvgl heap
#define LVGL_HEAP_SIZE (1024*100)
#define USE_START_ADD SDRAM_START_ADD

#endif

//LVGL_LCD_LINC.c file
//sizes
#define MY_DISP_HOR_RES       320U
#define MY_DISP_VER_RES       480U
#define MY_DISP_ROWS          (MY_DISP_VER_RES/8)
#define BYTE_PER_PIXEL       (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB565))

#define LVGL_DRAW_BUFFER_SIZE (MY_DISP_HOR_RES * MY_DISP_ROWS * BYTE_PER_PIXEL)
#define LVGL_SDRAM_BUF1_ADDRESS  (USE_START_ADD+LVGL_DRAW_BUFFER_SIZE)
#define LVGL_SDRAM_BUF2_ADDRESS  (LVGL_SDRAM_BUF1_ADDRESS + LVGL_DRAW_BUFFER_SIZE)

#define DMA2D_SDRAM_BUF3_SIZE    (MY_DISP_HOR_RES * MY_DISP_VER_RES * BYTE_PER_PIXEL)
#define DMA2D_SDRAM_BUF3_ADDRESS (LVGL_SDRAM_BUF2_ADDRESS + (MY_DISP_HOR_RES * MY_DISP_VER_RES * BYTE_PER_PIXEL))




#endif /* INC_USER_LIBS_SDRAM_ADD_MANIGMENT_H_ */
