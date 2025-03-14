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
	joystickXValue = joystickValues[1];
	joystickYValue = joystickValues[0];

	ssd1306_Fill(Black);

	char joystick_string[50];

	ssd1306_SetCursor(0,0);
	snprintf(joystick_string, sizeof(joystick_string), "x: %d", joystickXValue);
	ssd1306_WriteString(joystick_string, Font_7x10, White);
	//HAL_UART_Transmit(,raw_adc[1], sizeof(adc_string),1000);

	ssd1306_SetCursor(0,12);
	snprintf(joystick_string, sizeof(joystick_string), "y: %d", joystickYValue);
		ssd1306_WriteString(joystick_string, Font_7x10, White);

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









