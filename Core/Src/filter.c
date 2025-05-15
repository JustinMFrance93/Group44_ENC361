/*
 * filter.c
 *
 *  Created on: May 7, 2025
 *      Author: wfr19
 */
#include "filter.h"


void fir_filter_init(FIRFilter *filter, const int *coeffs) {
    for (int i = 0; i < N; i++) {
        filter->coeffs[i] = coeffs[i];
        filter->circ_buffer[i] = 0;
    }
    filter->index = 0;
}

int16_t fir_filter(FIRFilter *filter, int16_t input) {
    int32_t output = 0;

    filter->circ_buffer[filter->index] = input;

    for (int i = 0; i < N; i++) {
        output += filter->coeffs[i] * filter->circ_buffer[(filter->index - i + N) % N];
    }

    filter->index = (filter->index + 1) % N;

    return (int16_t) output / N;  // This division assumes averaging is intended
}
