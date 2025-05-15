/*
 * task_blinky.c
 *
 *  Created on: Mar 12, 2025
 *      Author: jfr125
 */
#include "task_blinky.h"
#include "gpio.h"
#include "numbers.h"
#include "pwm.h"
#include "rgb.h"



static uint32_t taskBlinkyNextRun;
static uint8_t duty = 0;
void task_blinky_init(void)
{
	taskBlinkyNextRun = HAL_GetTick() + TASK_BLINKY_PERIOD_TICKS;


}

void task_blinky_execute(void)
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

	rgb_colour_all_on();

	uint32_t goal_quart = nums.goal  / 4;
	uint32_t goal_half = nums.goal / 2;
	uint32_t goal_three_quart = (nums.goal / 4) * 3;




	if (nums.steps < goal_quart){
		duty = goal_quart * 10 /nums.steps;
	}
	if (nums.steps >= goal_half){
		duty = 100;
		rgb_led_on(RGB_RIGHT);

	}
	if (nums.steps >= goal_three_quart){
		rgb_led_on(RGB_DOWN);
	}
	if (nums.steps >= goal_three_quart){
		rgb_led_on(RGB_LEFT);

	}
	pwm_setDutyCycle(&htim2, TIM_CHANNEL_3, duty);
	uint8_t duty = pwm_getDutyCycle(&htim2, TIM_CHANNEL_3);
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
