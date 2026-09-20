/*
 * Buttons.c
 *
 *  Created on: 31 Aug 2026
 *      Author: reino
 */


#include "INCLUDES.hpp"



/*state_VAL is the variable that you want to change.
 * state_NUM is to total number of states for those variables
 * CIRCULAR is 1 one when you want the state to loop or 0 if you want the state_VAL to stop at the extreme values
 * HAL_GPIO_WritePin(RPM_OUT_GPIO_Port, RPM_OUT_Pin, SET);
 */

uint8_t UP_State=0;
uint8_t DOWN_State=0;
uint8_t ENTER_State=0;
uint8_t EXIT_State=0;




uint8_t UP_Event()
{
    static bool lastReading = false;
    static bool stablePressed = false;
    static bool armed = false;
    static uint32_t lastChange = 0;

    const uint32_t now = HAL_GetTick();
    const bool pressed =
        HAL_GPIO_ReadPin(UP_GPIO_Port, UP_Pin) == GPIO_PIN_RESET;

    if (pressed != lastReading) {
        lastReading = pressed;
        lastChange = now;
    }

    if ((uint32_t)(now - lastChange) >= 30U &&
        pressed != stablePressed) {

        stablePressed = pressed;

        if (stablePressed) {
            armed = true;       // Press confirmed; wait for release.
        } else if (armed) {
        	UP_State = 1;           // Release confirmed; signal event.
            armed = false;
        }
    }

    return UP_State;
}

uint8_t DOWN_Event()
{
    static bool lastReading = false;
    static bool stablePressed = false;
    static bool armed = false;
    static uint32_t lastChange = 0;

    const uint32_t now = HAL_GetTick();
    const bool pressed =
        HAL_GPIO_ReadPin(DOWN_GPIO_Port, DOWN_Pin) == GPIO_PIN_RESET;

    if (pressed != lastReading) {
        lastReading = pressed;
        lastChange = now;
    }

    if ((uint32_t)(now - lastChange) >= 30U &&
        pressed != stablePressed) {

        stablePressed = pressed;

        if (stablePressed) {
            armed = true;       // Press confirmed; wait for release.
        } else if (armed) {
        	DOWN_State = 1;           // Release confirmed; signal event.
            armed = false;
        }
    }

    return DOWN_State;
}

uint8_t ENTER_Event()
{
    static bool lastReading = false;
    static bool stablePressed = false;
    static bool armed = false;
    static uint32_t lastChange = 0;

    const uint32_t now = HAL_GetTick();
    const bool pressed =
        HAL_GPIO_ReadPin(ENTER_GPIO_Port, ENTER_Pin) == GPIO_PIN_RESET;

    if (pressed != lastReading) {
        lastReading = pressed;
        lastChange = now;
    }

    if ((uint32_t)(now - lastChange) >= 30U &&
        pressed != stablePressed) {

        stablePressed = pressed;

        if (stablePressed) {
            armed = true;       // Press confirmed; wait for release.
        } else if (armed) {
        	ENTER_State = 1;           // Release confirmed; signal event.
            armed = false;
        }
    }

    return ENTER_State;
}

uint8_t EXIT_Event()
{
    static bool lastReading = false;
    static bool stablePressed = false;
    static bool armed = false;
    static uint32_t lastChange = 0;

    const uint32_t now = HAL_GetTick();
    const bool pressed =
        HAL_GPIO_ReadPin(EXIT_GPIO_Port, EXIT_Pin) == GPIO_PIN_RESET;

    if (pressed != lastReading) {
        lastReading = pressed;
        lastChange = now;
    }

    if ((uint32_t)(now - lastChange) >= 30U &&
        pressed != stablePressed) {

        stablePressed = pressed;

        if (stablePressed) {
            armed = true;       // Press confirmed; wait for release.
        } else if (armed) {
        	EXIT_State = 1;           // Release confirmed; signal event.
            armed = false;
        }
    }

    return EXIT_State;
}

void EVENT_Reset()
{
UP_State=0;
DOWN_State=0;
ENTER_State=0;
EXIT_State=0;
	
}















































































































