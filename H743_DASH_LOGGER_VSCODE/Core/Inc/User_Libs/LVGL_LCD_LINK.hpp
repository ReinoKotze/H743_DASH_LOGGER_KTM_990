#ifndef INC_LVGL_LCD_LINK_H_
#define INC_LVGL_LCD_LINK_H_
#include "lvgl.h"
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif
extern volatile uint8_t TEFLAG;
extern volatile uint32_t lcd_te_period_ms;
void lv_port_disp_init(void);
void disp_enable_update(void);
void disp_disable_update(void);
bool lv_port_disp_service(void);
bool lv_port_disp_busy(void);
void lv_port_disp_mdma_complete_isr(bool success);
void lv_port_disp_te_isr(void);
#ifdef __cplusplus
}
#endif
#endif
