/*
 * task_accelarometer.c
 *
 *  Created on: May 7, 2025
 *      Author: wfr19
 */



#include "task_accelerometer.h"
#include "gpio.h"
#include "imu_lsm6ds.h"
#include "ssd1306_conf.h"
#include "ssd1306_fonts.h"
#include "ssd1306.h"
#include "task_joystick.h"
#include "stdio.h"
#include <string.h>
#include "usart.h"
#include "task_buttons.h"
#include "stdbool.h"

static uint32_t taskAccelerometerNextRun;


void task_accelerometer_init(void)
{
	taskAccelerometerNextRun = HAL_GetTick() + TASK_ACCELEROMETER_PERIOD_TICKS;
	// Enable accelerometer with high performance
	imu_lsm6ds_write_byte(CTRL1_XL, CTRL1_XL_HIGH_PERFORMANCE);


}

void task_accelerometer_execute(void)
{
	char acc_string_x[30] = {0};
	char acc_string_y[30] = {0};
	char acc_string_z[30] = {0};
	bool switch2_pressed = getSwitch2();

	uint8_t acc_x_low = imu_lsm6ds_read_byte(OUTX_L_XL);
	uint8_t acc_x_high = imu_lsm6ds_read_byte(OUTX_H_XL);

	uint8_t acc_y_low = imu_lsm6ds_read_byte(OUTY_L_XL);
	uint8_t acc_y_high = imu_lsm6ds_read_byte(OUTY_H_XL);

	uint8_t acc_z_low = imu_lsm6ds_read_byte(OUTZ_L_XL);
	uint8_t acc_z_high = imu_lsm6ds_read_byte(OUTZ_H_XL);

	int16_t acc_XValue = (int16_t)((acc_x_high << 8) | acc_x_low);
	snprintf(acc_string_x, sizeof(acc_string_x), "x: %6d  ", acc_XValue);

	int16_t acc_YValue = (int16_t)((acc_y_high << 8) | acc_y_low);
	snprintf(acc_string_y, sizeof(acc_string_y), "y: %6d  ", acc_YValue);

	int16_t acc_ZValue = (int16_t)((acc_z_high << 8) | acc_z_low);
	snprintf(acc_string_z, sizeof(acc_string_z), "z: %6d\n\r", acc_ZValue);

	if(switch2_pressed){
		HAL_UART_Transmit(&huart2, (uint8_t*)acc_string_x, sizeof(acc_string_x), 1000);
		HAL_UART_Transmit(&huart2, (uint8_t*)acc_string_y, sizeof(acc_string_y), 1000);
		HAL_UART_Transmit(&huart2, (uint8_t*)acc_string_z, sizeof(acc_string_z), 1000);

	}


}

uint32_t getTaskAccelerometer(void)
{
	return taskAccelerometerNextRun;
}

void setTaskAccelerometer(uint32_t nextRunTick)
{
    taskAccelerometerNextRun = nextRunTick;
}

void incrementTaskAccelerometer(void)
{
	taskAccelerometerNextRun += TASK_ACCELEROMETER_PERIOD_TICKS;
}

