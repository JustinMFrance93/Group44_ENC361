/*
 * adc_value.h
 *
 *  Created on: Apr 8, 2025
 *      Author: wfr19
 */

#ifndef INC_ADC_VALUE_H_
#define INC_ADC_VALUE_H_

#include "stdint.h"
#include <stdbool.h>



void process_adc_values(void);

uint16_t get_joystick_xposition(void);

uint16_t get_joystick_yposition(void);

bool get_joystick_xchanged(void);

bool get_joystick_ychanged(void) ;

uint16_t get_pot_step(void);

bool change_unit(void);


#endif /* INC_ADC_VALUE_H_ */
