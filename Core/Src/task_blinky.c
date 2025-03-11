/*
 * task_blinky.c
 *
 *  Created on: Mar 12, 2025
 *      Author: jfr125
 */


#include "task_blinky.h"
#include "app.h"
#include "gpio.h"




void task_blinky_execute(void) //LED
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}
