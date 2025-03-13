/*
 * task_display.h
 *
 *  Created on: Mar 12, 2025
 *      Author: jfr125
 */

#ifndef INC_TASK_DISPLAY_H_
#define INC_TASK_DISPLAY_H_

#define TASK_DISPLAY_FREQUENCY_HZ 4 //DISPLAY frequency
#define TASK_DISPLAY_PERIOD_TICKS (TICK_FREQUENCY_HZ/TASK_DISPLAY_FREQUENCY_HZ)

void screen_init (void);

void task_display_execute(void);

#endif /* INC_TASK_DISPLAY_H_ */
