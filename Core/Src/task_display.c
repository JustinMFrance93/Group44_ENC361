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
#include "stdio.h"
#include <string.h>
#include "usart.h"
#include "task_buttons.h"
#include <stdbool.h>


static uint32_t taskDisplayNextRun;
static uint16_t joystickXValue;
static uint16_t joystickYValue;

void task_display_init(void)
{
	taskDisplayNextRun = HAL_GetTick() + TASK_DISPLAY_PERIOD_TICKS;
	ssd1306_Init();


}

void task_display_execute(void) //LED
{
	uint16_t* joystickValues = getJoystickValues();
	bool switch2_pressed = getSwitch2();
	joystickXValue = joystickValues[1];
	joystickYValue = joystickValues[0];

	ssd1306_Fill(Black);

	char joystick_string_x[30] = {0};
	char joystick_string_y[30] = {0};
	uint8_t joystickXPercent = 0;
	char joystickXPosition[10] = "Rest";
	uint8_t joystickYPercent = 0;
	char joystickYPosition[10] = "Rest";

	ssd1306_SetCursor(0,0);
	if (joystickXValue < 2100) {
		joystickXPercent = (2100 - joystickXValue) * 100 / 2100;
		strcpy(joystickXPosition, "Right");
	}
	else if (joystickXValue > 2300) {
		joystickXPercent = (joystickXValue - 2300) * 100 / 1700;
		strcpy(joystickXPosition, "Left");
	}
	snprintf(joystick_string_x, sizeof(joystick_string_x), "x: %4d %s %d%% ", joystickXValue, joystickXPosition, joystickXPercent);
	ssd1306_WriteString(joystick_string_x, Font_7x10, White);



	ssd1306_SetCursor(0,12);
	if (joystickYValue < 2100) {
		joystickYPercent = (2100 - joystickYValue) * 100 / 2100;
		strcpy(joystickYPosition, "Up");
	}
	else if (joystickYValue > 2300) {
		joystickYPercent = (joystickYValue - 2300) * 100 / 1700;
		strcpy(joystickYPosition, "Down");
	}
	snprintf(joystick_string_y, sizeof(joystick_string_y), "y: %4d %s %d%%\n\r", joystickYValue, joystickYPosition, joystickYPercent);
	ssd1306_WriteString(joystick_string_y, Font_7x10, White);
    if(switch2_pressed)
    	{
    		HAL_UART_Transmit(&huart2, (const uint8_t *)joystick_string_x, sizeof(joystick_string_x), 1000);
    	    HAL_UART_Transmit(&huart2, (const uint8_t *)joystick_string_y, sizeof(joystick_string_y), 1000);

    	}




	ssd1306_UpdateScreen();
}

uint32_t getTaskDisplay(void) {
	return taskDisplayNextRun;
}

void setTaskDisplay(uint32_t nextRunTick) {
    taskDisplayNextRun = nextRunTick;
}

void incrementTaskDisplay(void) {
	taskDisplayNextRun += TASK_DISPLAY_PERIOD_TICKS;
}









