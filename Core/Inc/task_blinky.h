/*
 * task_blinky.h
 *
 *  Created on: Mar 12, 2025
 *      Author: jfr125
 */

#ifndef INC_TASK_BLINKY_H_
#define INC_TASK_BLINKY_H_

#define TASK_BLINKY_FREQUENCY_HZ 2 //LED frequency
#define TASK_BLINKY_PERIOD_TICKS (TICK_FREQUENCY_HZ/TASK_BLINKY_FREQUENCY_HZ)


void task_blinky_execute(void); //LED

#endif /* INC_TASK_BLINKY_H_ */
