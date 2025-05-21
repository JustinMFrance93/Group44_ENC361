/*
 * filter.c
 *
 *  Created on: May 7, 2025
 *      Author: wfr19
 */
#include "filter.h"
#include <stddef.h>

int16_t fir_filter(Buffer_t* buffer, int16_t input) {
    buffer->circ_buffer[buffer->index] = input;
    buffer->index ++;
    if (buffer->index >= N) {
    	buffer->index = 0;
    }

    int64_t output = 0;


    for (size_t i = 0; i < N; i++) {
        output += buffer->circ_buffer[i];
    }

    int32_t average = output / N;
    return (int16_t) average;  // This division assumes averaging is intended
}


