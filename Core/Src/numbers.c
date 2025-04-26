/*
 * numbers.c
 *
 *  Created on: Apr 25, 2025
 *      Author: wfr19
 */
#include "numbers.h"
#include "adc_value.h"
#include "state.h"
#include "stdbool.h"

#define PRESCALER  6000 //get to goal within 15 secs

static bool testmode = false;
static bool changeUnit = false;

numbers_t nums = {0,1000,0,0.0,0};

void step_count(){
	nums.step_percent = nums.steps * 100 / nums.goal;
	nums.kilometers = (nums.steps * 0.9) / 1000;
	nums.yards = nums.kilometers * 1094;
}

void step_increment() {
	if (get_state() != SET_GOAL) {
		nums.steps += 80;
	}
}

bool change_unit(void) {
	if (get_joystick_ychanged() && get_joystick_yposition() == 2 && !testmode) {
		changeUnit = !changeUnit;
	}
	return changeUnit;
}

uint32_t set_goal(uint32_t new_goal)
{
	nums.goal = new_goal;
	return nums.goal;
}

void toggle_test_mode(){
	testmode = !testmode;
}

bool get_test_mode() {
    return testmode;
}

void test_mode(){
	int32_t delta_steps = (get_y_percentage() * nums.goal) / PRESCALER;

	// yPosition == 2, joy stick up = increase step count
	if (get_joystick_yposition() == 2 && nums.steps < nums.goal) {
		if (nums.steps + delta_steps  > nums.goal){
			nums.steps = nums.goal;
		} else {
			nums.steps += delta_steps;
		}
	}
	// yPosition == 1, joy stick down = increase step count
	if (get_joystick_yposition() == 1 && nums.steps > 0) {
		if (nums.steps - delta_steps < 0) {
			nums.steps = 0;
		} else {
			nums.steps -= delta_steps;
		}
	}



	step_count();

}
