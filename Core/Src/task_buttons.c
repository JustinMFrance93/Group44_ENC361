/*
 * task_buttons.c
 *
 *  Created on: Mar 12, 2025
 *      Author: jfr125
 */

#include "task_buttons.h"
#include "buttons.h"
#include "rgb.h"
#include "gpio.h"
#include "pwm.h"
#include "numbers.h"
#include <stdbool.h>


static uint32_t taskButtonsNextRun;
static bool switch_pressed = false;
static uint32_t buttonCount;
static uint32_t last_reset_time = 0;


void task_buttons_init(void)
{
	buttons_init ();
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	taskButtonsNextRun = HAL_GetTick() + TASK_BUTTONS_PERIOD_TICKS;
}

void task_buttons_execute(void)
{
	uint32_t current_time = HAL_GetTick();

	//Set LED colour to white
	rgb_colour_all_on();

	//SW1 cycle through 10 stages of brightness on top LED
	if (buttons_checkButton(UP) == PUSHED) {
		step_increment();

		uint8_t duty = pwm_getDutyCycle(&htim2, TIM_CHANNEL_3);
		duty += 10;
		if (duty > 100) {
			duty = 0;
		}
		pwm_setDutyCycle(&htim2, TIM_CHANNEL_3, duty);
	}

	//SW2 toggle bottom LED
	if (buttons_checkButton(DOWN) == PUSHED) {
		buttonCount += 1;
		rgb_led_toggle(RGB_DOWN);
		switch_pressed = !switch_pressed;
	}

	//SW3 toggle right LED
	if (buttons_checkButton(RIGHT) == PUSHED) {
		rgb_led_toggle(RGB_RIGHT);
	}

	//SW4 toggle left LED
	if (buttons_checkButton(LEFT) == PUSHED) {
		rgb_led_toggle(RGB_LEFT);
	}

	if (current_time - last_reset_time >= 1200) {
		buttonCount = 0;
		last_reset_time = current_time;
	}

	if (buttonCount == 2){
		toggle_test_mode();
		buttonCount = 0;
	}

	buttons_update ();
}

uint32_t getTaskButtons(void)
{
	return taskButtonsNextRun;
}

bool getSwitch2(void)
{
	return switch_pressed;
}

void setTaskButtons(uint32_t nextRunTick)
{
    taskButtonsNextRun = nextRunTick;
}

void incrementTaskButtons(void)
{
	taskButtonsNextRun += TASK_BUTTONS_PERIOD_TICKS;
}




