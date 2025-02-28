/*
 * app.c
 *
 *  Created on: Feb 27, 2025
 *      Author: wfr19
 */
#include "gpio.h"
#include "rgb.h"

int app_main()
{
	while (1)
	{
		HAL_Delay(200);
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11))
		{
			rgb_led_on(RGB_UP);
			rgb_colour_all_on();
		}
		else
		{
			rgb_led_off(RGB_UP);

		}

		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1))
		{
			rgb_led_on(RGB_DOWN);
			rgb_colour_all_on();
		}
		else
		{
			rgb_led_off(RGB_DOWN);
		}

		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10))
		{
			rgb_led_on(RGB_RIGHT);
			rgb_colour_all_on();
		}
		else
		{
			rgb_led_off(RGB_RIGHT);
		}
		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13))
		{
			rgb_led_off(RGB_LEFT);

		}
		else
		{
			rgb_led_on(RGB_LEFT);
			rgb_colour_all_on();		}

	}
}
