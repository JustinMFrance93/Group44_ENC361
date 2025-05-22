/*
 * adc_value.c
 *
 *  Created on: Apr 8, 2025
 *      Author: wfr19
 */

#include "adc_value.h"
#include "adc.h"
#include <stdbool.h>

static uint16_t raw_adc[3];

static uint16_t joystickXValue;
static uint16_t joystickYValue;
static uint16_t potValue;
static uint16_t potStep;

static uint16_t xPosition = 0;
static uint16_t xPrevPosition = 0;
static bool xPositionChanged = false;

static uint16_t yPosition = 0;
static uint16_t yPrevPosition = 0;
static uint16_t yPercent = 0;
static bool yPositionChanged = false;

void process_adc_values(void) {

	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 3);
    joystickXValue = raw_adc[2];
    joystickYValue = raw_adc[1];

    potValue = ((raw_adc[0] - 147) * 14500 / 3948) + 500;
    potStep = (potValue / 500) * 500;



    if (joystickXValue < 1700) {
        xPosition = 2;
    }else if (joystickXValue > 2700) {
        xPosition = 1;
    } else {
        xPosition = 0;
    }


    xPositionChanged   = (xPosition != xPrevPosition);
    xPrevPosition = xPosition;

    if (joystickYValue < 2150) {
    	yPercent = (2150 - joystickYValue) * 100 / 1710;
        yPosition = 2;
    } else if (joystickYValue > 2350) {
		yPercent = (joystickYValue - 2350) * 100 / 1700;
    	yPosition = 1;
    } else {
		yPosition = 0;
    }

    yPositionChanged = (yPosition != yPrevPosition);
    yPrevPosition = yPosition;
}

// Getter functions for the processed ADC values
uint16_t get_joystick_xposition(void) {
    return xPosition;
}

uint16_t get_joystick_yposition(void){
	return yPosition;
}

uint16_t get_y_percentage(void){
	return yPercent;
}

bool get_joystick_xchanged(void) {
    return xPositionChanged;
}

bool get_joystick_ychanged(void) {
    return yPositionChanged;
}

uint16_t get_pot_step(void) {
    return potStep;
}



