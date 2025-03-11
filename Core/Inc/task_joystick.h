/*
 * task_joystick.h
 *
 *  Created on: Mar 12, 2025
 *      Author: jfr125
 */

#ifndef INC_TASK_JOYSTICK_H_
#define INC_TASK_JOYSTICK_H_

#define TASK_JOYSTICK_FREQUENCY_HZ 4 //Joystick frequency
#define TASK_JOYSTICK_PERIOD_TICKS (TICK_FREQUENCY_HZ/TASK_JOYSTICK_FREQUENCY_HZ)

void task_joystick_execute(void);

#endif /* INC_TASK_JOYSTICK_H_ */
