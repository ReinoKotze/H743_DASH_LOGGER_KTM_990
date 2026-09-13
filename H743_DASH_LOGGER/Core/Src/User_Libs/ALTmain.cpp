#include "main.h"
#include "User_Libs/w25q128.h"
#include "User_Libs/st7365_3.5Inch.h"
#include "User_Libs/bsp_sdram.h"
#include "User_Libs/LVGL_LCD_LINK.h"
#include "ALTmain.hpp"
#include "ui.h"
#include "Buttons.hpp"

////might use a STM32H743VIT6 in final board

extern "C" {
volatile uint32_t lcd_refresh_count;
volatile uint32_t lcd_fallback_count;
volatile uint32_t lcd_last_refresh_ms;
uint8_t screen_state=0;
uint8_t screen_stateNUM=1;


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


    LV_TIM_UPDATE();
    NON_BLOCKING_VSYNC();
    UI_Logic();








///////////////////////////
}


void UI_Logic()
{
    UP_Event();
    DOWN_Event();

    const bool upEvent = (UP_Event() == 1);
    const bool downEvent = (DOWN_Event() == 1);
/////////////

    if (upEvent) {
        screen_state = (screen_state >= screen_stateNUM)
            ? 0
            : screen_state + 1;

        UP_State = 0;
    }

    if (downEvent) {
        screen_state = (screen_state == 0)
            ? screen_stateNUM
            : screen_state - 1;

        DOWN_State = 0;
    }

////////////
switch (screen_state)
{
case 0:

    if (ui_Normal == nullptr) {
        ui_Normal_screen_init();
    }

    if (lv_screen_active() != ui_Normal) {
        lv_screen_load(ui_Normal);
    }

    if (ui_RAWsensor != nullptr) {
        ui_RAWsensor_screen_destroy();
    }

    break;

case 1:

    if (ui_RAWsensor == nullptr) {
        ui_RAWsensor_screen_init();
    }

    if (lv_screen_active() != ui_RAWsensor) {
        lv_screen_load(ui_RAWsensor);
    }

    if (ui_Normal != nullptr) {
        ui_Normal_screen_destroy();
    }

    RPM_UPDATE();
    SPEED_UPDATE();
    break;
default:
    break;
}
}




















void NON_BLOCKING_VSYNC()

{

    static uint32_t last_refresh_ms;
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


}
