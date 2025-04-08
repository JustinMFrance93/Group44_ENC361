/*
 * adc_value.h
 *
 *  Created on: Apr 8, 2025
 *      Author: wfr19
 */

#ifndef INC_ADC_VALUE_H_
#define INC_ADC_VALUE_H_

#include "stdint.h"


void process_adc_values(void);
uint16_t get_joystick_x(void);
uint16_t get_joystick_y(void);
uint16_t get_pot_step(void);

#endif /* INC_ADC_VALUE_H_ */
