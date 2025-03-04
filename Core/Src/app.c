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
//		HAL_Delay(200);
//		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); //LED 1

		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11)) //SW1
		{
			rgb_led_on(RGB_UP);
			rgb_colour_all_on();
		}
		else
		{
			rgb_led_off(RGB_UP);

		}

		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1)) //SW2
		{
			rgb_led_on(RGB_DOWN);
			rgb_colour_all_on();
		}
		else
		{
			rgb_led_off(RGB_DOWN);
		}

//		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10)) //SW3
//		{
//			rgb_led_on(RGB_RIGHT);
//			rgb_colour_all_on();
//		}
//		else
//		{
//			rgb_led_off(RGB_RIGHT);
//		}

		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)) //SW4
		{
			rgb_led_off(RGB_LEFT);

		}
		else
		{
			rgb_led_on(RGB_LEFT);
			rgb_colour_all_on();
		}



	}
}
void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
		{
			static int count;

			if (GPIO_Pin & GPIO_PIN_10)
			{
				count++;
				rgb_led_toggle(RGB_RIGHT);
			}
		}

