/*
 * state.c
 *
 *  Created on: Apr 8, 2025
 *      Author: wfr19
 */
#include "task_joystick.h"
#include "state.h"


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
				break;

		case DISTANCE_TRAVELLED:
				if (xValue == 1) {
					current_state = CURRENT_STEPS;
				}
				if (xValue == 2){
		   			current_state = GOAL_PROGRESS;
				}
				break;

	}
}

uint32_t get_state(void)
{
	return current_state;
}

