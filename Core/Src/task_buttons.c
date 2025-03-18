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
#include <stdbool.h>


static uint32_t taskButtonsNextRun;
static bool switch_pressed = false;

void task_buttons_init(void)
{
	buttons_init ();
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	taskButtonsNextRun = HAL_GetTick() + TASK_BUTTONS_PERIOD_TICKS;
}

void task_buttons_execute(void)
{
	//Set LED colour to white
	rgb_colour_all_on();

	//SW1 cycle through 10 stages of brightness on top LED
	if (buttons_checkButton(UP) == PUSHED) {
		uint8_t duty = pwm_getDutyCycle(&htim2, TIM_CHANNEL_3);
		duty += 10;
		if (duty > 100) {
			duty = 0;
		}
		pwm_setDutyCycle(&htim2, TIM_CHANNEL_3, duty);
	}

	//SW2 toggle bottom LED and serial transmit
	if (buttons_checkButton(DOWN) == PUSHED) {
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




