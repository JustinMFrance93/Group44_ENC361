/*
 * task_joystick.h
 *
 *  Created on: Mar 12, 2025
 *      Author: jfr125
 */

#ifndef INC_TASK_JOYSTICK_H_
#define INC_TASK_JOYSTICK_H_

#include <stdint.h>
#include "config.h"

#define TASK_JOYSTICK_FREQUENCY_HZ 4 //Joystick frequency
#define TASK_JOYSTICK_PERIOD_TICKS (TICK_FREQUENCY_HZ/TASK_JOYSTICK_FREQUENCY_HZ)

void task_joystick_init(void);

void task_joystick_execute(void);

uint32_t getTaskJoystick(void);

void setTaskJoystick(uint32_t nextRunTick);

void incrementTaskJoystick(void);

uint16_t* getJoystickValues(void);

#endif /* INC_TASK_JOYSTICK_H_ */
