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

void task_buttons_execute(void) //LED
{
	rgb_colour_all_on();

	if (buttons_checkButton(UP) == PUSHED) //SW1
		{
			uint8_t duty = pwm_getDutyCycle(&htim2, TIM_CHANNEL_3);
			duty += 10;
			if (duty > 100) {
				duty = 0;
			}
			pwm_setDutyCycle(&htim2, TIM_CHANNEL_3, duty);
		}


		if (buttons_checkButton(DOWN) == PUSHED) //SW2
		{
			rgb_led_toggle(RGB_DOWN);
			if (switch_pressed == true)
			{
				switch_pressed = false;
			} else {
				switch_pressed = true;
			}

		}

		if (buttons_checkButton(RIGHT) == PUSHED) //SW3
		{
			rgb_led_toggle(RGB_RIGHT);

		}

		if (buttons_checkButton(LEFT) == PUSHED) //SW4
		{
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




