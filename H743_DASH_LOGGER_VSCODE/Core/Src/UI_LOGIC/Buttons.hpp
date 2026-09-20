/*
 * BUTTONS.hpp
 *
 *  Created on: 12 Sept 2026
 *      Author: reino
 */

#ifndef SRC_UI_LOGIC_BUTTONS_HPP_
#define SRC_UI_LOGIC_BUTTONS_HPP_

//uint8_t Val;
extern uint8_t UP_State;
extern uint8_t DOWN_State;
extern uint8_t ENTER_State;
extern uint8_t EXIT_State;

uint8_t UP_Event();


uint8_t DOWN_Event();


uint8_t ENTER_Event();


uint8_t EXIT_Event();


void EVENT_Reset();



#endif /* SRC_UI_LOGIC_BUTTONS_HPP_ */
