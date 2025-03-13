/*
 * app.c
 *
 *  Created on: Feb 27, 2025
 *      Author: wfr19
 */

#include "adc.h"
#include "task_blinky.h"
#include "task_buttons.h"
#include "task_joystick.h"
#include "buttons.h"
#include "task_display.h"
#include "ssd1306_conf.h"
#include "ssd1306_fonts.h"
#include "ssd1306.h"

#define TICK_FREQUENCY_HZ 1000
#define HZ_TO_TICKS(FREQUENCY_HZ) (TICK_FREQUENCY_HZ/FREQUENCY_HZ)





static uint32_t taskBlinkyNextRun = 0;
static uint32_t taskButtonsNextRun = 0;
static uint32_t taskJoystickNextRun = 0;
static uint32_t taskDisplayNextRun = 0;


static uint16_t raw_adc[2];


int app_main()
{
	screen_init ();
	buttons_init ();
	taskBlinkyNextRun = HAL_GetTick() + TASK_BLINKY_PERIOD_TICKS;
	taskButtonsNextRun = HAL_GetTick() + TASK_BUTTONS_PERIOD_TICKS;
	taskJoystickNextRun = HAL_GetTick() + TASK_JOYSTICK_PERIOD_TICKS;
	taskDisplayNextRun = HAL_GetTick() + TASK_DISPLAY_PERIOD_TICKS;

	while (1)
	{
		uint32_t ticks = HAL_GetTick();

		if(ticks > taskBlinkyNextRun)
		{
		  task_blinky_execute();
		  taskBlinkyNextRun += TASK_BLINKY_PERIOD_TICKS;
		}

		if (ticks > taskButtonsNextRun)
		{
		  task_buttons_execute();
		  taskButtonsNextRun += TASK_BUTTONS_PERIOD_TICKS;
		}

		if (ticks > taskJoystickNextRun)
		{
		  task_joystick_execute();
		  taskJoystickNextRun += TASK_JOYSTICK_PERIOD_TICKS;
		}

		if(ticks > taskDisplayNextRun)
		{
			task_display_execute();
			taskDisplayNextRun += TASK_DISPLAY_PERIOD_TICKS;
		}

		HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 2);

		buttons_update ();


	}
}




void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{

}

