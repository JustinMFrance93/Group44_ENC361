/*
 * buzzer.h
 *
 *  Created on: Apr 9, 2025
 *      Author: jfr125
 */

#ifndef INC_TASK_BUZZER_H_
#define INC_TASK_BUZZER_H_

#include <stdint.h>
#include "config.h"

#define TASK_BUZZER_FREQUENCY_HZ 80 //BUZZER frequency
#define TASK_BUZZER_PERIOD_TICKS (TICK_FREQUENCY_HZ/TASK_BUZZER_FREQUENCY_HZ)

void task_buzzer_init(void);

void task_buzzer_execute(void);

uint32_t getTaskBuzzer(void);

void setTaskBuzzer(uint32_t nextRunTick);
void incrementTaskBuzzer(void);


#endif /* INC_TASK_BUZZER_H_ */
