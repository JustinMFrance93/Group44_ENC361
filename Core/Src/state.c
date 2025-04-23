/*
 * state.c
 *
 *  Created on: Apr 8, 2025
 *      Author: wfr19
 */
#include "adc_value.h"
#include "state.h"
#include "buttons.h"
#include "task_display.h"



static state_t current_state = CURRENT_STEPS;


void step_counter_state(void) {

	uint16_t xValue = get_joystick_xposition();

	switch (current_state) {

		case CURRENT_STEPS:
			if (xValue == 1) {
				current_state = GOAL_PROGRESS;
			}
			if (xValue == 2){
				current_state = DISTANCE_TRAVELLED;
			}
			break;

		case GOAL_PROGRESS:
			if (xValue == 1) {
				current_state = DISTANCE_TRAVELLED;
			}
			if (xValue == 2){
				current_state = CURRENT_STEPS;
			}

			if (buttons_checkButton(JOY) == RELEASED) {
				if (buttons_getHoldDuration(JOY) >= 1000) {
					current_state = SET_GOAL;
				}
			}
			break;

		case DISTANCE_TRAVELLED:
			if (xValue == 1) {
				current_state = CURRENT_STEPS;
			}
			if (xValue == 2){
				current_state = GOAL_PROGRESS;
			}
			break;

		case SET_GOAL:
			if (buttons_checkButton(JOY) == RELEASED) {
				if (buttons_getHoldDuration(JOY) > 1000) {
					setGoal(get_pot_step());
				}
				current_state = GOAL_PROGRESS;
			}
			break;

	}
}

uint32_t get_state(void)
{
	return current_state;
}

