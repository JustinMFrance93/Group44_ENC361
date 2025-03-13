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

void screen_init (void)
{
	ssd1306_Init();
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString("Hello world!", Font_7x10, White);

}


void task_display_execute(void)
{
	ssd1306_UpdateScreen();
}


