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
#define N 10
#define NVAR_THRESHOLD 10000000
static bool testmode = false;
static bool changeUnit = false;

static uint32_t mean_acc = 0;
static uint32_t prev_acc_mag = 0;
static uint32_t acc_mag_buffer[N] = {0};


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

void detect_steps(){
	char mag_string[30] = {0};
	char mean_string[30] = {0};
	char nvar_string[30] = {0};
	char thresh_string[30] = {0};
	uint32_t acc_mag = get_acceleration_mag();


    // Shift buffer to make room for new value
    for (int i = N - 1; i > 0; i--) {
        acc_mag_buffer[i] = acc_mag_buffer[i - 1];
    }
    acc_mag_buffer[0] = acc_mag;

    // Compute mean
    uint32_t sum = 0;
    for (int i = 0; i < N; i++) {
        sum += acc_mag_buffer[i];
    }
    mean_acc = sum / N;

    // Compute variance (Nvar)
    uint32_t Nvar = 0;
    for (int i = 0; i < N; i++) {
        int32_t diff = acc_mag_buffer[i] - mean_acc;
        Nvar += diff * diff;
    }

    // Step detection condition
    if ((acc_mag > mean_acc) && (prev_acc_mag < mean_acc) && (Nvar > NVAR_THRESHOLD)) {
        nums.steps++;
    }

    prev_acc_mag = acc_mag;

    snprintf(mag_string, sizeof(mag_string), "MAG:%-15lu", acc_mag);
    snprintf(mean_string, sizeof(mean_string), "MEAN:%-15lu", mean_acc);
    snprintf(nvar_string, sizeof(nvar_string), "Nvar:%-15lu", Nvar);
    snprintf(thresh_string, sizeof(thresh_string), "steps:%-15d\n\r", nums.steps);

    // Now print all the strings on the same line

    HAL_UART_Transmit(&huart2, (uint8_t*)mag_string, sizeof(mag_string), 1000);
	HAL_UART_Transmit(&huart2, (uint8_t*)mean_string, sizeof(mean_string), 1000);
	HAL_UART_Transmit(&huart2, (uint8_t*)nvar_string, sizeof(nvar_string), 1000);
	HAL_UART_Transmit(&huart2, (uint8_t*)thresh_string, sizeof(thresh_string), 1000);
}
