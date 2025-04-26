/*
 * task_buzzer.c
 *
 *  Created on: Apr 9, 2025
 *      Author: jfr125
 */

#include "task_buzzer.h"
#include "gpio.h"
#include "pwm.h"
#include "tim.h"
#include "numbers.h"

static uint32_t taskBuzzerNextRun;

void task_buzzer_init(void)
{
	taskBuzzerNextRun = HAL_GetTick() + TASK_BUZZER_PERIOD_TICKS;
}

void task_buzzer_execute(void)
{
	if (nums.steps == nums.goal){
		pwm_setDutyCycle(&htim16, TIM_CHANNEL_1, 50);
	} else {
		pwm_setDutyCycle(&htim16, TIM_CHANNEL_1, 0);

	}

}

uint32_t getTaskBuzzer(void)
{
	return taskBuzzerNextRun;
}

void setTaskBuzzer(uint32_t nextRunTick)
{
    taskBuzzerNextRun = nextRunTick;
}

void incrementTaskBuzzer(void)
{
	taskBuzzerNextRun += TASK_BUZZER_PERIOD_TICKS;
}

