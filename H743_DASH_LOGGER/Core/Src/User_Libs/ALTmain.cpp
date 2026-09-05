#include "main.h"
#include "User_Libs/w25q128.h"
#include "User_Libs/st7365_3.5Inch.h"
#include "User_Libs/bsp_sdram.h"
#include "User_Libs/LVGL_LCD_LINK.h"
#include "ALTmain.hpp"
#include "ui.h"

extern "C" {
volatile uint32_t lcd_refresh_count;
volatile uint32_t lcd_fallback_count;
volatile uint32_t lcd_last_refresh_ms;

void setup()
{
    HAL_Delay(5U);
    CSP_QUADSPI_Init();
    CSP_QSPI_EnableMemoryMappedMode();
    if(SDRAM_InitSequence() != HAL_OK) Error_Handler();
    LCD_Init();
    lv_init();
    lv_tick_set_cb(HAL_GetTick);
    lv_port_disp_init();
    ui_init();
}

void tasks()
{
    static uint32_t last_refresh_ms;
    RPM_UPDATE();
    LV_TIM_UPDATE();
    if(lv_port_disp_busy()) return;
    bool te_due = lv_port_disp_service();
    uint32_t now = HAL_GetTick();
    /* Restore the simple TE-driven loop, with a 33 ms missing-TE fallback. */
    if(te_due || (uint32_t)(now - last_refresh_ms) >= 33U) {
        if(!te_due) ++lcd_fallback_count;
        ++lcd_refresh_count;
        uint32_t before = HAL_GetTick();
        lv_display_refr_timer(NULL);
        last_refresh_ms = HAL_GetTick();
        lcd_last_refresh_ms = last_refresh_ms - before;
        /* Wait for a fresh edge on the next iteration, without blocking. */
        (void)lv_port_disp_service();
    }
}
void LV_TIM_UPDATE()
{
    static uint32_t last_timer_ms;
    uint32_t mask = __get_PRIMASK();
    __disable_irq();
    uint8_t due = lvgl_timer_due;
    lvgl_timer_due = 0U;
    __set_PRIMASK(mask);
    uint32_t now = HAL_GetTick();
    if(due || (uint32_t)(now - last_timer_ms) >= 5U) {
        last_timer_ms = now;
        lv_timer_handler();
    }
}

void RPM_UPDATE()
{
    static uint32_t last_update;
    static uint32_t previous = UINT32_MAX;
    uint32_t now = HAL_GetTick();
    if((uint32_t)(now - last_update) < 16U) return;
    last_update = now;
    uint32_t value = rpm;
    if((uint32_t)(now - rpm_last_capture_ms) > 30U) value = 0U;
    if(value != previous) {
        lv_label_set_text_fmt(ui_rpmVALUE, "rpm= %04lu", (unsigned long)value);
        previous = value;
    }
}
}