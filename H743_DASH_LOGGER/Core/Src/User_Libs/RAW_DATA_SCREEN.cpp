/*
 * RAW_DATA.c
 *
 *  Created on: 9 Sept 2026
 *      Author: reino
 *
 *      this file updates the the variables on the
 *      raw data screen. it shows the data measured
 *      by all sensors that the system has access to
 */
#include "main.h"
#include "User_Libs/w25q128.h"
#include "User_Libs/st7365_3.5Inch.h"
#include "User_Libs/bsp_sdram.h"
#include "User_Libs/LVGL_LCD_LINK.h"
#include "ALTmain.hpp"
#include "ui.h"

void Raw_Data()
{

	RPM_UPDATE();

}

void RPM_UPDATE()
{

//    static uint32_t last_update;
//    static uint32_t previous = UINT32_MAX;
//    uint32_t now = HAL_GetTick();
//    if((uint32_t)(now - last_update) < 16U) return;
//    last_update = now;
//    uint32_t value = rpm;
//
//   // lv_label_set_text_fmt(ui_rpmVALUE, "rpm= %04lu", (unsigned long)value);
//
//    if((uint32_t)(now - rpm_last_capture_ms) > 30U) value = 0U;
//    if(value != previous) {
//        lv_label_set_text_fmt(ui_rpmVALUE, "rpm= %04lu", (unsigned long)value);
//        previous = value;
//    }



    static uint32_t last_update;
    const uint32_t now = HAL_GetTick();

    if ((uint32_t)(now - last_update) < 16U) return;
    last_update = now;

    uint32_t value = rpm;

    if ((uint32_t)(now - rpm_last_capture_ms) > 30U) {
        value = 0U;
    }

    lv_label_set_text_fmt(
        ui_rpmVALUE, "rpm= %04lu", (unsigned long)value);
}

void SPEED_UPDATE();
