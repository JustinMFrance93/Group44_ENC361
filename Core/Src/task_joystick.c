/*
 * task_joystick.c
 *
 *  Created on: Mar 12, 2025
 *      Author: jfr125
 */
#include "task_joystick.h"
#include "gpio.h"
#include "adc.h"
#include "stdio.h"

static uint32_t taskJoystickNextRun;
static uint16_t raw_adc[2];

void task_joystick_init(void)
{
	taskJoystickNextRun = HAL_GetTick() + TASK_JOYSTICK_PERIOD_TICKS;
}

void task_joystick_execute(void)
{
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 2);
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

uint16_t* getJoystickValues(void)
{
	return raw_adc;
}
