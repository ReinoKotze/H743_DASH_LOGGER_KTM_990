/*
 * ALTmain.hpp
 *
 *  Created on: 2 Sept 2026
 *      Author: reino
 */

#ifndef INC_USER_LIBS_ALTMAIN_HPP_
#define INC_USER_LIBS_ALTMAIN_HPP_

// If compiled by a C++ compiler, use C-linkage for these functions
#ifdef __cplusplus
extern "C" {
#endif
// Declare flat C-style wrappers for your C++ functionality


extern volatile uint32_t rpm;
extern volatile uint32_t rpm_last_capture_ms;
extern volatile uint8_t lvgl_timer_due;
extern volatile uint8_t LV_HAS_RUN;

void LV_TIM_UPDATE();
void RPM_UPDATE ();


#ifdef __cplusplus
}
#endif

#endif // MY_CPP_CODE_H




