/*
 * app.c
 *
 *  Created on: Feb 27, 2025
 *      Author: wfr19
 */
#include "gpio.h"
#include "rgb.h"
#include "buttons.h"
#include "adc.h"

#define TICK_FREQUENCY_HZ 1000
#define HZ_TO_TICKS(FREQUENCY_HZ) (TICK_FREQUENCY_HZ/FREQUENCY_HZ)

#define TASK_LED_FREQUENCY_HZ 2 //LED frequency
#define TASK_BUTTONS_FREQUENCY_HZ 25 //Buttons frequency
#define TASK_JOYSTICK_FREQUENCY_HZ 25 //Joystick frequency

#define TASK_LED_PERIOD_TICKS (TICK_FREQUENCY_HZ/TASK_LED_FREQUENCY_HZ)
#define TASK_BUTTONS_PERIOD_TICKS (TICK_FREQUENCY_HZ/TASK_BUTTONS_FREQUENCY_HZ)
#define TASK_JOYSTICK_PERIOD_TICKS (TICK_FREQUENCY_HZ/TASK_JOYSTICK_FREQUENCY_HZ)

static uint32_t taskLedNextRun = 0;
static uint32_t taskButtonsNextRun = 0;
static uint32_t taskJoystickNextRun = 0;

static uint16_t raw_adc[2];

void task_led_execute(void);
void task_buttons_execute(void);
void task_joystick_execute(void);


int app_main()
{
	buttons_init ();
	taskLedNextRun = HAL_GetTick() + TASK_LED_PERIOD_TICKS;
	taskButtonsNextRun = HAL_GetTick() + TASK_BUTTONS_PERIOD_TICKS;
	taskJoystickNextRun = HAL_GetTick() + TASK_JOYSTICK_PERIOD_TICKS;


	while (1)
	{
		uint32_t ticks = HAL_GetTick();

		if(ticks > taskLedNextRun)
		{
		  task_led_execute();
		  taskLedNextRun += TASK_LED_PERIOD_TICKS;
		}

		if (ticks > taskButtonsNextRun)
		{
		  task_buttons_execute();
		  taskButtonsNextRun += TASK_BUTTONS_PERIOD_TICKS;
		}

		if (ticks > taskJoystickNextRun)
		{
		  task_joystick_execute();
		  taskJoystickNextRun += TASK_JOYSTICK_PERIOD_TICKS;
		}

		HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 2);

		buttons_update ();
	}
}

void task_led_execute(void) //LED
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}

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

void task_joystick_execute(void) //joystick
{

}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{

}

