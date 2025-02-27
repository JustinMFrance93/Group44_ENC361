/*
 * app.c
 *
 *  Created on: Feb 27, 2025
 *      Author: wfr19
 */
#include "gpio.h"

int app_main()
{
	while (1)
	{
		HAL_Delay(200);
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11))
		{
		  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET);
		}
		else
		{
		  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET);
		}
	}
}
