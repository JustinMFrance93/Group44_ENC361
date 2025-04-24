/*
 * task_display.c
 *
 *  Created on: Mar 12, 2025
 *      Author: jfr125
 */
#include "task_display.h"
#include "gpio.h"
#include "ssd1306_conf.h"
#include "ssd1306_fonts.h"
#include "ssd1306.h"
#include "task_joystick.h"
#include "adc_value.h"
#include "stdio.h"
#include <string.h>
#include "usart.h"
#include "task_buttons.h"
#include <stdbool.h>
#include "state.h"

static uint32_t taskDisplayNextRun;
static uint32_t steps = 100;
static uint32_t goal = 1000;




void task_display_init(void)
{
	taskDisplayNextRun = HAL_GetTick() + TASK_DISPLAY_PERIOD_TICKS;
	ssd1306_Init();
}

void task_display_execute(void)
{


	state_t state = get_state();

	ssd1306_Fill(Black);
	ssd1306_SetCursor(0,0);
	char title_string[30] = {0};
	char value_string[30] = {0};
	int stepsPercent = steps * 100 / goal;
	float kilometers = (steps * 0.9) / 1000;
	int yards = kilometers * 1094;

	if (state == CURRENT_STEPS){
		snprintf(title_string, sizeof(title_string), "Current Steps:");
		ssd1306_WriteString(title_string, Font_7x10, White);


		ssd1306_SetCursor(0,12);
		if (change_unit()) {
			snprintf(value_string, sizeof(value_string), "Steps: %d%%",stepsPercent);
		} else {
			snprintf(value_string, sizeof(value_string), "Steps: %lu",steps);
		}
		ssd1306_WriteString(value_string, Font_7x10, White);

	}

	if (state == GOAL_PROGRESS){
		snprintf(title_string, sizeof(title_string), "Goal Progress:");
		ssd1306_WriteString(title_string, Font_7x10, White);
		ssd1306_SetCursor(0,12);

		snprintf(value_string, sizeof(value_string), "%lu / %lu",steps, goal);
		ssd1306_WriteString(value_string, Font_7x10, White);
	}

	if (state == DISTANCE_TRAVELLED){
		snprintf(title_string, sizeof(title_string), "Distance Traveled:");
		ssd1306_WriteString(title_string, Font_7x10, White);

		ssd1306_SetCursor(0,12);
				if (change_unit()) {
					snprintf(value_string, sizeof(value_string), "Distance: %.3f km",kilometers);
				} else {
						snprintf(value_string, sizeof(value_string), "Distance: %d yd",yards);
				}
				ssd1306_WriteString(value_string, Font_7x10, White);
	}
	if (state == SET_GOAL){
			snprintf(title_string, sizeof(title_string), "Set Goal:");
			ssd1306_WriteString(title_string, Font_7x10, White);
			ssd1306_SetCursor(0,12);

			snprintf(value_string, sizeof(value_string), "Goal: %d",get_pot_step());
			ssd1306_WriteString(value_string, Font_7x10, White);
	}



	ssd1306_UpdateScreen();
}

uint32_t getTaskDisplay(void)
{
	return taskDisplayNextRun;
}

uint32_t setGoal(uint32_t new_goal)
{
	goal = new_goal;
	return goal;
}

void setTaskDisplay(uint32_t nextRunTick)
{
    taskDisplayNextRun = nextRunTick;
}

void incrementTaskDisplay(void)
{
	taskDisplayNextRun += TASK_DISPLAY_PERIOD_TICKS;
}









