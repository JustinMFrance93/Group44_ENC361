/*
 * numbers.c
 *
 *  Created on: Apr 25, 2025
 *      Author: wfr19
 */
#include "numbers.h"
#include "adc_value.h"

numbers_t nums = {0,1000,0,0.0,0};

void step_count(){
	nums.step_percent = nums.steps * 100 / nums.goal;
	nums.kilometers = (nums.steps * 0.9) / 1000;
	nums.yards = nums.kilometers * 1094;
}

void step_incremnt() {
	nums.steps += 80;
}

uint32_t setGoal(uint32_t new_goal)
{
	nums.goal = new_goal;
	return nums.goal;
}

