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
#include "INCLUDES.hpp"

static void setLabelIfChanged(lv_obj_t *label, const char *text)
{
    if (label != nullptr && strcmp(lv_label_get_text(label), text) != 0) {
        lv_label_set_text(label, text);
    }
}

static void formatAdcUnavailable(char *text, size_t length, const char *name)
{
    if (strcmp(name, "Engine") == 0) {
        snprintf(text, length, "ADC W:%04lX R:%04lX",
                 (unsigned long)ads1115_last_config_written,
                 (unsigned long)ads1115_last_config_read);
    } else {
        snprintf(text, length, "I:%lu S:%02lX H:%lu E:%02lX",
                 (unsigned long)ads1115_i2c_error_count,
                 (unsigned long)ads1115_last_error_stage,
                 (unsigned long)ads1115_last_hal_status,
                 (unsigned long)ads1115_last_hal_error);
    }
}

void Raw_Data()
{

	RPM_UPDATE();

}

void RPM_UPDATE()
{
    static uint32_t last_update;
    const uint32_t now = HAL_GetTick();

    if ((uint32_t)(now - last_update) < 16U) return;
    last_update = now;

    uint32_t value = rpm;

    if ((uint32_t)(now - rpm_last_capture_ms) > 30U) {
        value = 0U;
    }

    char text[32];
    snprintf(text, sizeof(text), "rpm= %04lu", (unsigned long)value);
    setLabelIfChanged(ui_rpmVALUE, text);
}

void SPEED_UPDATE()
{
	 static uint32_t last_update;
	    const uint32_t now = HAL_GetTick();

	    if ((uint32_t)(now - last_update) < 16U) return;
	    last_update = now;

	    uint32_t value = SPEED;

	    if ((uint32_t)(now - SPEED_last_capture_ms) > 200U) {
	        value = 0U;
	    }

    char text[32];
    snprintf(text, sizeof(text), "km/h= %04lu", (unsigned long)value);
    setLabelIfChanged(ui_speedVALUE, text);

}

void TEMP_VOLTAGE_UPDATE()
{
    static uint32_t last_update;
    const uint32_t now = HAL_GetTick();
    if ((uint32_t)(now - last_update) < 100U) return;
    last_update = now;

    int32_t millivolts = 0;
    char text[32];
    if (ADS1115::ReadMillivolts(ADS1115::EngineChannel, &millivolts)) {
        snprintf(text, sizeof(text), "Engine: %ld.%03ld V",
                 (long)(millivolts / 1000), (long)(millivolts % 1000));
    } else {
        formatAdcUnavailable(text, sizeof(text), "Engine");
    }
    setLabelIfChanged(ui_engineTempVALUE, text);

    if (ADS1115::ReadMillivolts(ADS1115::AmbientChannel, &millivolts)) {
        snprintf(text, sizeof(text), "Ambient: %ld.%03ld V",
                 (long)(millivolts / 1000), (long)(millivolts % 1000));
    } else {
        formatAdcUnavailable(text, sizeof(text), "Ambient");
    }
    setLabelIfChanged(ui_AmbientTempVALUE, text);
}
