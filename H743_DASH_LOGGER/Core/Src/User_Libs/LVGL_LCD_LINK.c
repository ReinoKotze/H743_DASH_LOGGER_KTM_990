#include "User_Libs/LVGL_LCD_LINK.h"
#include "User_Libs/st7365_3.5Inch.h"
#include "SDRAM_ADD_MANIGMENT.h"
#include <string.h>

/* Internal D2 SRAM. Explicitly clear these NOLOAD buffers before use. */
static uint8_t draw1[LVGL_DRAW_BUFFER_SIZE]
    __attribute__((section(".lvgl_draw_buffers"), aligned(32)));
static uint8_t draw2[LVGL_DRAW_BUFFER_SIZE]
    __attribute__((section(".lvgl_draw_buffers"), aligned(32)));
static bool updates_enabled = true;
static lv_display_t * volatile flushing_display;
volatile uint32_t lcd_mdma_flush_count;
volatile uint32_t lcd_mdma_complete_count;
volatile uint32_t lcd_mdma_errors;
static volatile uint8_t refresh_pending;
volatile uint8_t TEFLAG;
volatile uint32_t lcd_te_count;
volatile uint32_t lcd_te_period_ms;
static volatile uint32_t last_te_ms;

static void disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *pixels)
{
    if(!updates_enabled) {
        lv_display_flush_ready(disp);
        return;
    }
    if(pixels == NULL || area->x1 < 0 || area->y1 < 0 ||
       area->x2 < area->x1 || area->y2 < area->y1 ||
       area->x2 >= MY_DISP_HOR_RES || area->y2 >= MY_DISP_VER_RES) {
        Error_Handler();
        return;
    }
    uint32_t width = (uint32_t)(area->x2 - area->x1 + 1);
    uint32_t rows = (uint32_t)(area->y2 - area->y1 + 1);
    uint32_t stride = lv_display_get_buf_active(disp)->header.stride;
    if(stride < width * 2U || (stride & 1U) != 0U ||
       rows > LVGL_DRAW_BUFFER_SIZE / stride) {
        Error_Handler();
        return;
    }
    if(flushing_display != NULL) {
        ++lcd_mdma_errors;
        Error_Handler();
        return;
    }
    /* PARTIAL mode redraws each buffer before reuse. Compact padded rows in
       place so MDMA can stream the exact rectangle without padding pixels. */
    uint32_t row_bytes = width * 2U;
    if(stride != row_bytes) {
        for(uint32_t y = 1; y < rows; ++y)
            memmove(pixels + y * row_bytes, pixels + y * stride, row_bytes);
    }
    flushing_display = disp;
    ++lcd_mdma_flush_count;
    /* Driver cleans source D-cache and splits transfers into bounded chunks. */
    if(LCD_StartBitmapMDMA_IT((uint16_t)area->x1, (uint16_t)area->y1,
                             (uint16_t)area->x2, (uint16_t)area->y2,
                             (const uint16_t *)pixels) != HAL_OK) {
        ++lcd_mdma_errors;
        Error_Handler();
    }
    /* Only the final completion IRQ releases this buffer to LVGL. */
}

bool lv_port_disp_busy(void) { return flushing_display != NULL; }

void lv_port_disp_mdma_complete_isr(bool success)
{
    if(!success) {
        ++lcd_mdma_errors;
        Error_Handler();
        return;
    }
    lv_display_t *disp = flushing_display;
    if(disp != NULL) {
        ++lcd_mdma_complete_count;
        lv_display_flush_ready(disp);
        flushing_display = NULL;
    }
}
void lv_port_disp_init(void)
{
    memset(draw1, 0, sizeof(draw1));
    memset(draw2, 0, sizeof(draw2));
    lv_display_t *disp = lv_display_create(MY_DISP_HOR_RES, MY_DISP_VER_RES);
    lv_display_set_color_format(disp, LV_COLOR_FORMAT_RGB565);
    lv_display_set_buffers(disp, draw1, draw2, LVGL_DRAW_BUFFER_SIZE,
                           LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_set_flush_cb(disp, disp_flush);
    lv_display_delete_refr_timer(disp);
    lv_display_set_default(disp);
}

void disp_enable_update(void) { updates_enabled = true; }
void disp_disable_update(void) { updates_enabled = false; }

/* PD3 TE publishes one coalesced event; it never renders or waits. */
void lv_port_disp_te_isr(void)
{
    uint32_t now = HAL_GetTick();
    if(lcd_te_count != 0U) lcd_te_period_ms = now - last_te_ms;
    last_te_ms = now;
    ++lcd_te_count;
    refresh_pending = 1U;
    TEFLAG = 1U;
}

bool lv_port_disp_service(void)
{
    uint32_t mask = __get_PRIMASK();
    __disable_irq();
    bool pending = refresh_pending != 0U;
    refresh_pending = 0U;
    __set_PRIMASK(mask);
    return pending;
}