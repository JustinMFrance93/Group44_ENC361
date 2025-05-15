/*
 * filter.h
 *
 *  Created on: May 7, 2025
 *      Author: wfr19
 */

#ifndef INC_FILTER_H_
#define INC_FILTER_H_

#include "stdint.h"


#define N 10  // Number of coefficients

typedef struct {
    uint8_t coeffs[N];       // Filter coefficients
    uint16_t circ_buffer[N];  // Circular buffer
    uint8_t index;           // Circular buffer index
} FIRFilter;

// Initializes the filter with coefficients
void fir_filter_init(FIRFilter *filter, const int *coeffs);

// Applies the filter and returns the filtered result
int16_t fir_filter(FIRFilter *filter, int16_t input);
#endif
