/*
 * adc_value.c
 *
 *  Created on: Apr 8, 2025
 *      Author: wfr19
 */

#include "adc_value.h"
#include "adc.h"

static uint16_t raw_adc[3];


static uint16_t joystickXValue;
static uint16_t joystickYValue;
static uint16_t potValue;
static uint16_t potStep;



void process_adc_values(void) {
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 3);
    joystickXValue = raw_adc[2];
    joystickYValue = raw_adc[1];
    potValue = ((raw_adc[0] - 147) * 14500 / 3948) + 500;
    potStep = (potValue / 500) * 500;
}

// Getter functions for the processed ADC values
uint16_t get_joystick_x(void) {
    return joystickXValue;
}

uint16_t get_joystick_y(void) {
    return joystickYValue;
}

uint16_t get_pot_step(void) {
    return potStep;
}


