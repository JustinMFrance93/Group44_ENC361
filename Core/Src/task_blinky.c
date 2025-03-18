/*
 * task_blinky.c
 *
 *  Created on: Mar 12, 2025
 *      Author: jfr125
 */
#include "task_blinky.h"
#include "gpio.h"

static uint32_t taskBlinkyNextRun;

void task_blinky_init(void)
{
	taskBlinkyNextRun = HAL_GetTick() + TASK_BLINKY_PERIOD_TICKS;
}

void task_blinky_execute(void)
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}

uint32_t getTaskBlinky(void)
{
	return taskBlinkyNextRun;
}

void setTaskBlinky(uint32_t nextRunTick)
{
    taskBlinkyNextRun = nextRunTick;
}

void incrementTaskBlinky(void)
{
	taskBlinkyNextRun += TASK_BLINKY_PERIOD_TICKS;
}
