/*
 * state.h
 *
 *  Created on: Apr 9, 2025
 *      Author: wfr19
 */

#ifndef INC_STATE_H_
#define INC_STATE_H_

void step_counter_state(void);

typedef enum {
	CURRENT_STEPS,
	GOAL_PROGRESS,
	DISTANCE_TRAVELLED,
}state_t;

void step_counter_state(void);

uint32_t get_state(void);


#endif /* INC_STATE_H_ */
