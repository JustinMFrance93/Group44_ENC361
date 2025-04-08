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

static uint32_t taskDisplayNextRun;



void task_display_init(void)
{
	taskDisplayNextRun = HAL_GetTick() + TASK_DISPLAY_PERIOD_TICKS;
	ssd1306_Init();
}

void task_display_execute(void)
{
	//Get necessary values from button and joystick modules
	uint16_t joystickXValue = get_joystick_x();
	uint16_t joystickYValue = get_joystick_y();
	uint16_t potStep = get_pot_step();

	bool switch2_pressed = getSwitch2();


	ssd1306_Fill(Black);

	// Initialize strings
	char joystick_string_x[30] = {0};
	char joystick_string_y[30] = {0};
	char pot_string[30] = {0};


	uint8_t joystickXPercent = 0;
	char joystickXPosition[10] = "Rest";
	uint8_t joystickYPercent = 0;
	char joystickYPosition[10] = "Rest";

	//Write X position on display
	ssd1306_SetCursor(0,0);
	if (joystickXValue < 2100) {
		joystickXPercent = (2100 - joystickXValue) * 100 / 1640;
		strcpy(joystickXPosition, "Right");
	}
	else if (joystickXValue > 2300) {
		joystickXPercent = (joystickXValue - 2300) * 100 / 1675;
		strcpy(joystickXPosition, "Left");
	}
	if (joystickXPercent > 100) {
		joystickXPercent = 100;
	}
	snprintf(joystick_string_x, sizeof(joystick_string_x), "x: %4d %s %d%% ", joystickXValue, joystickXPosition, joystickXPercent);
	ssd1306_WriteString(joystick_string_x, Font_7x10, White);

	//Write Y position on display
	ssd1306_SetCursor(0,12);
	if (joystickYValue < 2150) {
		joystickYPercent = (2150 - joystickYValue) * 100 / 1710;
		strcpy(joystickYPosition, "Up");
	}
	else if (joystickYValue > 2350) {
		joystickYPercent = (joystickYValue - 2350) * 100 / 1700;
		strcpy(joystickYPosition, "Down");
	}
	if (joystickYPercent > 100) {
		joystickYPercent = 100;
	}
	snprintf(joystick_string_y, sizeof(joystick_string_y), "y: %4d %s %d%%\n\r", joystickYValue, joystickYPosition, joystickYPercent);
	ssd1306_WriteString(joystick_string_y, Font_7x10, White);

	//Write Pot value on display
	ssd1306_SetCursor(0,24);

	snprintf(pot_string, sizeof(pot_string), "pot: %d", potStep);
	ssd1306_WriteString(pot_string, Font_7x10, White);


	//Toggle Serial Transmit when Sw2 is pressed
	if(switch2_pressed) {
		HAL_UART_Transmit(&huart2, (const uint8_t *)joystick_string_x, sizeof(joystick_string_x), 1000);
		HAL_UART_Transmit(&huart2, (const uint8_t *)joystick_string_y, sizeof(joystick_string_y), 1000);
	}

	ssd1306_UpdateScreen();
}

uint32_t getTaskDisplay(void)
{
	return taskDisplayNextRun;
}

void setTaskDisplay(uint32_t nextRunTick)
{
    taskDisplayNextRun = nextRunTick;
}

void incrementTaskDisplay(void)
{
	taskDisplayNextRun += TASK_DISPLAY_PERIOD_TICKS;
}









