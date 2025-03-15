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

	char joystick_string_x[14] = {0};
	char joystick_string_y[14] = {0};

	ssd1306_SetCursor(0,0);
	snprintf(joystick_string_x, sizeof(joystick_string_x), "x: %4d  ", joystickXValue);
	ssd1306_WriteString(joystick_string_x, Font_7x10, White);



	ssd1306_SetCursor(0,12);
	snprintf(joystick_string_y, sizeof(joystick_string_y), "y: %4d\r\n", joystickYValue);
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









