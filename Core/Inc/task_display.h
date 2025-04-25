/*
 * task_display.h
 *
 *  Created on: Mar 12, 2025
 *      Author: jfr125
 */

#ifndef INC_TASK_DISPLAY_H_
#define INC_TASK_DISPLAY_H_

#include <stdint.h>
#include "config.h"

#define TASK_DISPLAY_FREQUENCY_HZ 4 //DISPLAY frequency
#define TASK_DISPLAY_PERIOD_TICKS (TICK_FREQUENCY_HZ/TASK_DISPLAY_FREQUENCY_HZ)

void task_display_init(void);

void task_display_execute(void);

uint32_t getTaskDisplay(void);

//uint32_t setGoal(uint32_t new_goal);

void setTaskDisplay(uint32_t nextRunTick);

void incrementTaskDisplay(void);

#endif /* INC_TASK_DISPLAY_H_ */
