/*
 * task_accelerometer.h
 *
 *  Created on: May 7, 2025
 *      Author: wfr19
 */

#ifndef INC_TASK_ACCELEROMETER_H_
#define INC_TASK_ACCELEROMETER_H_

#include <stdint.h>
#include "config.h"

#define TASK_ACCELEROMETER_FREQUENCY_HZ 80 //ACCELEROMETER frequency
#define TASK_ACCELEROMETER_PERIOD_TICKS (TICK_FREQUENCY_HZ/TASK_ACCELEROMETER_FREQUENCY_HZ)

void task_accelerometer_init(void);

void task_accelerometer_execute(void);

uint32_t getTaskAccelerometer(void);

void setTaskAccelerometer(uint32_t nextRunTick);
void incrementTaskAccelerometer(void);

uint32_t get_acceleration_mag(void);


#endif /* INC_TASK_ACCELEROMETER_H_ */
