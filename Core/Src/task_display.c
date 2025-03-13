/*
 * task_display.c
 *
 *  Created on: Mar 12, 2025
 *      Author: jfr125
 */

#include "task_display.h"
#include "app.h"
#include "ssd1306_conf.h"
#include "ssd1306_fonts.h"
#include "ssd1306.h"
#include "adc.h"
#include "stdio.h"

static uint16_t raw_adc[2];

void screen_init (void)
{
	ssd1306_Init();
	ssd1306_SetCursor(0, 0);


}


void task_display_execute(void)
{
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 2);
	ssd1306_SetCursor(0,0);
	char adc_string[50];
	snprintf(adc_string, sizeof(adc_string), "x: %d", raw_adc[1]);
	ssd1306_WriteString(adc_string, Font_7x10, White);
	HAL_UART_Transmit(,raw_adc[1], sizeof(adc_string),1000);

	ssd1306_SetCursor(0,12);
	char adc_string_two[50];
	snprintf(adc_string_two, sizeof(adc_string_two), "y: %d", raw_adc[0]);
	ssd1306_WriteString(adc_string_two, Font_7x10, White);
	ssd1306_UpdateScreen();
}


