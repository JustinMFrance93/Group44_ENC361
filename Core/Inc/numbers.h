/*
 * numbers.h
 *
 *  Created on: Apr 25, 2025
 *      Author: wfr19
 */

#ifndef INC_NUMBERS_H_
#define INC_NUMBERS_H_

#include "stdint.h"
#include <stdbool.h>

typedef struct {
	int32_t steps;
    uint32_t goal;
    uint32_t step_percent;
    uint32_t kilometers_x1000;
    uint32_t kilometers_int;
	uint32_t kilometers_frac;
    uint32_t yards;
} numbers_t;

extern numbers_t nums;

void step_count();

void step_increment();

bool change_unit(void) ;

uint32_t set_goal(uint32_t new_goal);

void toggle_test_mode();

bool get_test_mode();

void test_mode();

void detect_steps();

#endif /* INC_NUMBERS_H_ */
