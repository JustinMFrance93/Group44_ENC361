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
#include "filter.h"
#include "numbers.h"


#define X_OFFSET 200
#define Y_OFFSET -240
#define Z_OFFSET -100

static uint32_t taskAccelerometerNextRun;
static uint32_t magnitude = 0;


static Buffer_t x_accel_filter = {{0}, 0};
static Buffer_t y_accel_filter = {{0}, 0};
static Buffer_t z_accel_filter = {{0}, 0};

//static int16_t previous_outputX = 0;
//static int16_t previous_outputY = 0;
//static int16_t previous_outputZ = 0;


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


	detect_steps();


	uint8_t acc_x_low = imu_lsm6ds_read_byte(OUTX_L_XL);
	uint8_t acc_x_high = imu_lsm6ds_read_byte(OUTX_H_XL);

	uint8_t acc_y_low = imu_lsm6ds_read_byte(OUTY_L_XL);
	uint8_t acc_y_high = imu_lsm6ds_read_byte(OUTY_H_XL);

	uint8_t acc_z_low = imu_lsm6ds_read_byte(OUTZ_L_XL);
	uint8_t acc_z_high = imu_lsm6ds_read_byte(OUTZ_H_XL);

	int16_t acc_XValue = (int16_t)((acc_x_high << 8) | acc_x_low);
	int16_t acc_YValue = (int16_t)((acc_y_high << 8) | acc_y_low);
	int16_t acc_ZValue = (int16_t)((acc_z_high << 8) | acc_z_low);

	int16_t filtered_x = (fir_filter(&x_accel_filter, acc_XValue)) + X_OFFSET;
	int16_t filtered_y = (fir_filter(&y_accel_filter, acc_YValue)) + Y_OFFSET;
	int16_t filtered_z = (fir_filter(&z_accel_filter, acc_ZValue)) + Z_OFFSET;

//	int32_t filtered_x = (ar_filter(acc_XValue, &previous_outputX)); // 100;
//	int32_t filtered_y = (ar_filter(acc_YValue, &previous_outputY)); // 100;
//	int32_t filtered_z = (ar_filter(acc_ZValue, &previous_outputZ)); // 100;

	magnitude = filtered_x * filtered_x + filtered_y * filtered_y + filtered_z * filtered_z;

	snprintf(acc_string_x, sizeof(acc_string_x), " %-6d  ", filtered_x);
	snprintf(acc_string_y, sizeof(acc_string_y), " %-6d  ", filtered_y);
	snprintf(acc_string_z, sizeof(acc_string_z), " %-6d", filtered_z);



	HAL_UART_Transmit(&huart2, (uint8_t*)acc_string_x, sizeof(acc_string_x), 1000);
	HAL_UART_Transmit(&huart2, (uint8_t*)acc_string_y, sizeof(acc_string_y), 1000);
	HAL_UART_Transmit(&huart2, (uint8_t*)acc_string_z, sizeof(acc_string_z), 1000);


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

uint32_t get_acceleration_mag(void) {
    return magnitude;
}
