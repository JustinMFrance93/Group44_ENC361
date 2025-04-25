/*
 * numbers.h
 *
 *  Created on: Apr 25, 2025
 *      Author: wfr19
 */

#ifndef INC_NUMBERS_H_
#define INC_NUMBERS_H_

#include "stdint.h"

typedef struct {
	uint32_t steps;
    uint32_t goal;
    uint32_t step_percent;
    float kilometers;
    uint32_t yards;
} numbers_t;

extern numbers_t nums;

void step_count();
void step_incremnt();
uint32_t setGoal(uint32_t new_goal);


#endif /* INC_NUMBERS_H_ */
