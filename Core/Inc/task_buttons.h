/*
 * task_buttons.h
 *
 *  Created on: Mar 12, 2025
 *      Author: jfr125
 */

#ifndef INC_TASK_BUTTONS_H_
#define INC_TASK_BUTTONS_H_

#define TASK_BUTTONS_FREQUENCY_HZ 25 //Buttons frequency
#define TASK_BUTTONS_PERIOD_TICKS (TICK_FREQUENCY_HZ/TASK_BUTTONS_FREQUENCY_HZ)


void task_buttons_execute(void);

#endif /* INC_TASK_BUTTONS_H_ */
