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

static state_t current_state = GOAL_PROGRESS;
static state_t previous_state = GOAL_PROGRESS;
static bool xMoveOk =  true;

void step_counter_state(void) {

	uint16_t xValue = get_joystick_xposition();
    bool xReady = (xValue != 0 && xMoveOk);
    if (xValue == 0) {
    	xMoveOk = true;
    }

    if (current_state != previous_state) {
        if (current_state == GOAL_PROGRESS) {
            buttons_reset(JOY);
        }
        previous_state = current_state;
    }



    switch (current_state) {
        case CURRENT_STEPS:
            if (xReady) {
                if (xValue == 1) current_state = GOAL_PROGRESS;
                else if (xValue == 2) current_state = DISTANCE_TRAVELLED;
                xMoveOk = false;
            }
            break;

        case GOAL_PROGRESS:

            if (xReady) {
                if (xValue == 1) current_state = DISTANCE_TRAVELLED;
                else if (xValue == 2) current_state = CURRENT_STEPS;
                xMoveOk = false;
            }

            if (buttons_checkButton(JOY) == RELEASED && buttons_getHoldDuration(JOY) >= 1000) {
                current_state = SET_GOAL;
            }
            break;

        case DISTANCE_TRAVELLED:
            if (xReady) {
                if (xValue == 1) current_state = CURRENT_STEPS;
                else if (xValue == 2) current_state = GOAL_PROGRESS;
                xMoveOk = false;

            }
            break;

        case SET_GOAL:
            if (buttons_checkButton(JOY) == RELEASED) {
                if (buttons_getHoldDuration(JOY) > 1000) {
                    set_goal(get_pot_step());
                }
                current_state = GOAL_PROGRESS;
            }
            break;
    }
}

uint32_t get_state(void) {
    return current_state;
}
