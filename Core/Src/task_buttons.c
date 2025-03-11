/*
 * task_buttons.c
 *
 *  Created on: Mar 12, 2025
 *      Author: jfr125
 */

#include "task_buttons.h"
#include "app.h"
#include "buttons.h"
#include "rgb.h"

void task_buttons_execute(void) //Buttons
{
	if (buttons_checkButton(UP) == PUSHED) //SW1
	{
		rgb_colour_all_on();
		rgb_led_toggle(RGB_UP);
	}


	if (buttons_checkButton(DOWN) == PUSHED) //SW2
	{
		rgb_colour_all_on();
		rgb_led_toggle(RGB_DOWN);

	}

	if (buttons_checkButton(RIGHT) == PUSHED) //SW3
	{
		rgb_colour_all_on();
		rgb_led_toggle(RGB_RIGHT);

	}

	if (buttons_checkButton(LEFT) == PUSHED) //SW4
	{
		rgb_colour_all_on();
		rgb_led_toggle(RGB_LEFT);

	}
}
