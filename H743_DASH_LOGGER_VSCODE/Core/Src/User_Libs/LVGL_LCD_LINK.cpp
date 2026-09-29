

#include "INCLUDES.hpp"
/* Internal D2 SRAM. Explicitly clear these NOLOAD buffers before use. */

static uint8_t * const draw1 =
    (uint8_t *)LVGL_SDRAM_BUF1_ADDRESS;

static uint8_t * const draw2 =
    (uint8_t *)LVGL_SDRAM_BUF2_ADDRESS;



static bool updates_enabled = true;
static lv_display_t * volatile flushing_display;
static volatile uint8_t refresh_pending;
volatile uint8_t TEFLAG;
volatile uint32_t lcd_te_period_ms;
static volatile uint32_t last_te_ms;
static volatile bool te_time_valid;

/* A 60 Hz TE pulse arrives every 16-17 ms. Edges closer than this are
   electrical glitches/ringing and must not start another refresh. */
static constexpr uint32_t LCD_TE_MIN_PERIOD_MS = 12U;

#if USE_EXTERNAL_SDRAM
/* MDMA reads this internal AXI SRAM scanline instead of reading SDRAM while
   simultaneously writing the LCD through the same FMC controller. */
alignas(32) static uint8_t lcd_internal_stage[MY_DISP_HOR_RES * 2U];
#if LCD_SDRAM_VERIFY_READS
alignas(32) static uint8_t lcd_internal_verify[MY_DISP_HOR_RES * 2U];
#endif

struct LcdStagedFlush {
    const uint8_t *source;
    uint32_t row_bytes;
    uint16_t x0;
    uint16_t x1;
    uint16_t next_y;
    uint16_t rows_remaining;
    uint8_t write_passes_remaining;
    bool active;
};

static LcdStagedFlush staged_flush = {};

static inline void settle_shared_fmc_bus(void)
{
    __DSB();
    for(volatile uint32_t cycle = 0U;
        cycle < LCD_FMC_SETTLE_CYCLES;
        ++cycle) {
        __NOP();
    }
    __DSB();
}

static HAL_StatusTypeDef start_next_staged_row(void)
{
    if(!staged_flush.active || staged_flush.rows_remaining == 0U ||
       staged_flush.row_bytes > sizeof(lcd_internal_stage)) {
        return HAL_ERROR;
    }

    /* The previous MDMA completion ended an LCD write. Leave the shared data
       bus idle before changing direction and reading the SDRAM scanline. */
#if LCD_SDRAM_VERIFY_READS
    bool verified = false;
    for(uint32_t attempt = 0U;
        attempt < LCD_SDRAM_READ_RETRIES;
        ++attempt) {
        settle_shared_fmc_bus();
        memcpy(lcd_internal_stage,
               staged_flush.source,
               staged_flush.row_bytes);

        settle_shared_fmc_bus();
        memcpy(lcd_internal_verify,
               staged_flush.source,
               staged_flush.row_bytes);

        if(memcmp(lcd_internal_stage,
                  lcd_internal_verify,
                  staged_flush.row_bytes) == 0) {
            verified = true;
            break;
        }

    }

    if(!verified) {
        memcpy(lcd_internal_stage,
               lcd_internal_verify,
               staged_flush.row_bytes);
    }
#else
    settle_shared_fmc_bus();
    memcpy(lcd_internal_stage, staged_flush.source, staged_flush.row_bytes);
#endif

    /* Complete the SDRAM read, then leave another idle interval before MDMA
       changes the shared FMC pins back to LCD writes. */
    settle_shared_fmc_bus();
    staged_flush.write_passes_remaining = LCD_SCANLINE_WRITE_PASSES;

    return LCD_StartBitmapMDMA_IT(staged_flush.x0,
                                  staged_flush.next_y,
                                  staged_flush.x1,
                                  staged_flush.next_y,
                                  reinterpret_cast<const uint16_t *>(
                                      lcd_internal_stage));
}
#endif





static void disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *pixels)
{
    if(!updates_enabled) {
        lv_display_flush_ready(disp);
        return;
    }
    if(pixels == NULL || area->x1 < 0 || area->y1 < 0 ||
      area->x2 >= static_cast<int32_t>(MY_DISP_HOR_RES) ||
      area->y2 >= static_cast<int32_t>(MY_DISP_VER_RES)) {
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

#if USE_EXTERNAL_SDRAM
    staged_flush.source = pixels;
    staged_flush.row_bytes = row_bytes;
    staged_flush.x0 = static_cast<uint16_t>(area->x1);
    staged_flush.x1 = static_cast<uint16_t>(area->x2);
    staged_flush.next_y = static_cast<uint16_t>(area->y1);
    staged_flush.rows_remaining = static_cast<uint16_t>(rows);
    staged_flush.active = true;

    if(start_next_staged_row() != HAL_OK) {
        staged_flush.active = false;
        flushing_display = NULL;
        Error_Handler();
    }
#else
    /* Internal RAM_D2 can feed the LCD MDMA directly. */
    if(LCD_StartBitmapMDMA_IT(static_cast<uint16_t>(area->x1),
                             static_cast<uint16_t>(area->y1),
                             static_cast<uint16_t>(area->x2),
                             static_cast<uint16_t>(area->y2),
                             reinterpret_cast<const uint16_t *>(pixels)) != HAL_OK) {
        flushing_display = NULL;
        Error_Handler();
    }
#endif
    /* Only the final completion IRQ releases this buffer to LVGL. */
}

bool lv_port_disp_busy(void) { return flushing_display != NULL; }

void lv_port_disp_mdma_complete_isr(bool success)
{
    if(!success) {
#if USE_EXTERNAL_SDRAM
        staged_flush.active = false;
#endif
        Error_Handler();
        return;
    }

#if USE_EXTERNAL_SDRAM
    if(staged_flush.active) {
        if(staged_flush.write_passes_remaining > 1U) {
            --staged_flush.write_passes_remaining;
            settle_shared_fmc_bus();

            if(LCD_StartBitmapMDMA_IT(
                   staged_flush.x0,
                   staged_flush.next_y,
                   staged_flush.x1,
                   staged_flush.next_y,
                   reinterpret_cast<const uint16_t *>(lcd_internal_stage)) != HAL_OK) {
                staged_flush.active = false;
                Error_Handler();
            }
            return;
        }

        --staged_flush.rows_remaining;
        staged_flush.source += staged_flush.row_bytes;
        ++staged_flush.next_y;

        if(staged_flush.rows_remaining != 0U) {
            if(start_next_staged_row() != HAL_OK) {
                staged_flush.active = false;
                Error_Handler();
            }
            return;
        }

        staged_flush.active = false;
    }
#endif

    lv_display_t *disp = flushing_display;
    if(disp != NULL) {
        lv_display_flush_ready(disp);
        flushing_display = NULL;
    }
}
void lv_port_disp_init(void)
{
	memset(draw1, 0, LVGL_DRAW_BUFFER_SIZE);
	memset(draw2, 0, LVGL_DRAW_BUFFER_SIZE);

    lv_display_t *disp = lv_display_create(MY_DISP_HOR_RES, MY_DISP_VER_RES);
    lv_display_set_color_format(disp, LV_COLOR_FORMAT_RGB565);
    lv_display_set_buffers(disp, draw1, draw2, LVGL_DRAW_BUFFER_SIZE,LV_DISPLAY_RENDER_MODE_PARTIAL);
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

    if(te_time_valid)
    {
        uint32_t elapsed_ms = now - last_te_ms;
        if(elapsed_ms < LCD_TE_MIN_PERIOD_MS)
        {
            return;
        }
        lcd_te_period_ms = elapsed_ms;
    }

    last_te_ms = now;
    te_time_valid = true;
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
