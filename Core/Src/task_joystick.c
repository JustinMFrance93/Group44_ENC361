/*
 * task_joystick.c
 *
 *  Created on: Mar 12, 2025
 *      Author: jfr125
 */
#include "task_joystick.h"
#include "gpio.h"
#include "stdio.h"
#include "adc_value.h"

static uint32_t taskJoystickNextRun;


void task_joystick_init(void)
{
	taskJoystickNextRun = HAL_GetTick() + TASK_JOYSTICK_PERIOD_TICKS;
}

void task_joystick_execute(void)
{
	process_adc_values();
}

uint32_t getTaskJoystick(void)
{
	return taskJoystickNextRun;
}

void setTaskJoystick(uint32_t nextRunTick)
{
    taskJoystickNextRun = nextRunTick;
}

void incrementTaskJoystick(void)
{
	taskJoystickNextRun += TASK_JOYSTICK_PERIOD_TICKS;
}


