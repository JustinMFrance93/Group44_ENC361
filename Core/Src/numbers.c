/*
 * numbers.c
 *
 *  Created on: Apr 25, 2025
 *      Author: wfr19
 */
#include "numbers.h"
#include "adc_value.h"
#include "task_accelerometer.h"
#include "stdio.h"
#include <string.h>
#include "usart.h"
#include "state.h"
#include "stdbool.h"

#define PRESCALER  6000 //get to goal within 15 secs
#define WINDOW 100
#define NVAR_THRESHOLD 1000000000000000

#define HYSTERESIS_MARGIN 2800000000
#define STEP_DELAY 500

static bool testmode = false;
static bool changeUnit = false;
static bool step_ready = true;

static uint32_t last_step_tick = 0;
static uint32_t mean_acc = 0;
static uint32_t prev_acc_mag = 0;
static uint32_t acc_mag_buffer[WINDOW] = {0};
static uint8_t acc_mag_index = 0;


numbers_t nums = {0,1000,0,0,0,0,0};

void step_count(){
	nums.step_percent = nums.steps * 100 / nums.goal;
	nums.kilometers_x1000 = (nums.steps * 900) / 1000;
	nums.kilometers_int = nums.kilometers_x1000 / 1000;
	nums.kilometers_frac = nums.kilometers_x1000 % 1000;
	nums.yards = (nums.kilometers_x1000 * 1094) / 1000;
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


void detect_steps(){
	char mag_string[30] = {0};
	char mean_string[30] = {0};
	char nvar_string[30] = {0};
	uint32_t acc_mag = get_acceleration_mag() ;

	acc_mag_buffer[acc_mag_index] = acc_mag;
	acc_mag_index = (acc_mag_index + 1) % WINDOW;


    // Compute mean
    uint64_t sum = 0;
    for (int i = 0; i < WINDOW; i++) {
        sum += acc_mag_buffer[i];
    }
    mean_acc = sum / WINDOW;

    // Compute variance (Nvar)
    uint64_t Nvar = 0;
    for (int i = 0; i < WINDOW; i++) {
		int64_t diff = (int64_t)acc_mag_buffer[i] - (int64_t)mean_acc;
		Nvar += (uint64_t)(diff * diff);
    }

    uint32_t current_tick = HAL_GetTick();


    // Step detection condition
    if (step_ready && (acc_mag > mean_acc) && (prev_acc_mag < mean_acc) && (Nvar > NVAR_THRESHOLD)) {
        nums.steps++;
        step_ready = false;
        last_step_tick = current_tick;
    }


    if (!step_ready && mean_acc < (HYSTERESIS_MARGIN)&&  (current_tick - last_step_tick > STEP_DELAY)){
        step_ready = true;
    }

    prev_acc_mag = acc_mag;

    snprintf(mag_string, sizeof(mag_string), "%-15lu", acc_mag);
    snprintf(mean_string, sizeof(mean_string), "%-15lu", mean_acc);
    snprintf(nvar_string, sizeof(nvar_string), "%-15lu\n\r", Nvar);

    // Now print all the strings on the same line

    HAL_UART_Transmit(&huart2, (uint8_t*)mag_string, sizeof(mag_string), 1000);
	HAL_UART_Transmit(&huart2, (uint8_t*)mean_string, sizeof(mean_string), 1000);
	HAL_UART_Transmit(&huart2, (uint8_t*)nvar_string, sizeof(nvar_string), 1000);
}
