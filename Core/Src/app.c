/*
 * app.c
 *
 *  Created on: Feb 27, 2025
 *      Author: wfr19
 */
#include "gpio.h"
#include "rgb.h"
#include "buttons.h"

int app_main()
{
	buttons_init ();
	while (1)
	{
		HAL_Delay(40);
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

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

		buttons_update ();

	}
}
