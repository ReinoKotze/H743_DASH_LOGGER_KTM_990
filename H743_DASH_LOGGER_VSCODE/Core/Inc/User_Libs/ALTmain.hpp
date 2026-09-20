/*
 * ALTmain.hpp
 *
 *  Created on: 2 Sept 2026
 *      Author: reino
 */

#ifndef INC_USER_LIBS_ALTMAIN_HPP_
#define INC_USER_LIBS_ALTMAIN_HPP_

#include "User_Libs/interrupts.h"

// If compiled by a C++ compiler, use C-linkage for these functions
#ifdef __cplusplus
extern "C" {
#endif
// Declare flat C-style wrappers for your C++ functionality

void NON_BLOCKING_VSYNC();
void LV_TIM_UPDATE();

//used in RAW DATA,
void RPM_UPDATE ();
void SPEED_UPDATE();
void TEMP_VOLTAGE_UPDATE();
void UI_Logic();

//RAW data file
void Raw_Data();

#ifdef __cplusplus
}
#endif

#endif // MY_CPP_CODE_H




