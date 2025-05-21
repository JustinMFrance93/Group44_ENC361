/*
 * filter.h
 *
 *  Created on: May 7, 2025
 *      Author: wfr19
 */

#ifndef INC_FILTER_H_
#define INC_FILTER_H_

#include "stdint.h"


#define N 32  // Number of coefficients

typedef struct {
    uint32_t circ_buffer[N];  // Circular buffer
    uint8_t index;           // Circular buffer index
} Buffer_t;

int16_t fir_filter(Buffer_t* filter, int16_t input);
#endif
