/*
 * task_buttons.c
 *
 *  Created on: Mar 12, 2025
 *      Author: jfr125
 */

#include "task_buttons.h"
#include "app.h"
#include "buttons.h"
#include "rgb.h"
#include "gpio.h"


static uint32_t taskButtonsNextRun;

void task_buttons_init(void)
{
	buttons_init ();
	taskButtonsNextRun = HAL_GetTick() + TASK_BUTTONS_PERIOD_TICKS;
}

void task_buttons_execute(void) //LED
{
	if (buttons_checkButton(UP) == PUSHED) //SW1
		{
			rgb_colour_all_on();
			rgb_led_toggle(RGB_UP);
		}


		if (buttons_checkButton(DOWN) == PUSHED) //SW2
		{
			rgb_colour_all_on();
			rgb_led_toggle(RGB_DOWN);

		}

		if (buttons_checkButton(RIGHT) == PUSHED) //SW3
		{
			rgb_colour_all_on();
			rgb_led_toggle(RGB_RIGHT);

		}

		if (buttons_checkButton(LEFT) == PUSHED) //SW4
		{
			rgb_colour_all_on();
			rgb_led_toggle(RGB_LEFT);
		}

		buttons_update ();

}

uint32_t getTaskButtons(void)
{
	return taskButtonsNextRun;
}

void setTaskButtons(uint32_t nextRunTick)
{
    taskButtonsNextRun = nextRunTick;
}

void incrementTaskButtons(void)
{
	taskButtonsNextRun += TASK_BUTTONS_PERIOD_TICKS;
}




