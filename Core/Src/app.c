/*
 * app.c
 *
 *  Created on: Feb 27, 2025
 *      Author: wfr19
 */
#include "gpio.h"
#include "rgb.h"
#include "buttons.h"

#define TICK_FREQUENCY_HZ 1000
#define HZ_TO_TICKS(FREQUENCY_HZ) (TICK_FREQUENCY_HZ/FREQUENCY_HZ)

#define TASK_ONE_FREQUENCY_HZ 2
#define TASK_TWO_FREQUENCY_HZ 25

#define TASK_ONE_PERIOD_TICKS (TICK_FREQUENCY_HZ/TASK_ONE_FREQUENCY_HZ)
#define TASK_TWO_PERIOD_TICKS (TICK_FREQUENCY_HZ/TASK_TWO_FREQUENCY_HZ)

static uint32_t taskOneNextRun = 0;
static uint32_t taskTwoNextRun = 0;

void task_one_execute(void);
void task_two_execute(void);

int app_main()
{
	buttons_init ();
	taskOneNextRun = HAL_GetTick() + TASK_ONE_PERIOD_TICKS;
	taskTwoNextRun = HAL_GetTick() + TASK_TWO_PERIOD_TICKS;

	while (1)
	{
		uint32_t ticks = HAL_GetTick();

		if(ticks > taskOneNextRun)
		{
		  task_one_execute();
		  taskOneNextRun += TASK_ONE_PERIOD_TICKS;
		}

		if (ticks > taskTwoNextRun)
		{
		  task_two_execute();
		  taskTwoNextRun += TASK_TWO_PERIOD_TICKS;
		}

		buttons_update ();
	}
}

void task_one_execute(void) //LED
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}

void task_two_execute(void) //Buttons
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
}
