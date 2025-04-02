/*
 * app.c
 *
 *  Created on: Feb 27, 2025
 *      Author: wfr19
 */
//Milestone 1
#include "adc.h"
#include "task_blinky.h"
#include "task_buttons.h"
#include "task_joystick.h"
#include "task_display.h"
#include "config.h"

#define HZ_TO_TICKS(FREQUENCY_HZ) (TICK_FREQUENCY_HZ/FREQUENCY_HZ)

int app_main()
{
	task_buttons_init ();
	task_blinky_init();
	task_joystick_init();
	task_display_init();

	while (1)
	{
		uint32_t ticks = HAL_GetTick();

		if(ticks > getTaskBlinky()) {
		  task_blinky_execute();
		  incrementTaskBlinky();
		}

		if(ticks > getTaskButtons()) {
		  task_buttons_execute();
		  incrementTaskButtons();
		}

		if(ticks > getTaskJoystick()) {
		  task_joystick_execute();
		  incrementTaskJoystick();
		}

		if(ticks > getTaskDisplay()) {
		  task_display_execute();
		  incrementTaskDisplay();
		}


	}
}





