/*
 * task_buzzer.c
 *
 *  Created on: Apr 9, 2025
 *      Author: jfr125
 */

#include "task_buzzer.h"
#include "gpio.h"
#include "pwm.h"
#include "tim.h"
#include "numbers.h"
#include "stdbool.h"

static uint32_t taskBuzzerNextRun;
static uint32_t buzzerStartTime;
static bool buzzerActive;


void task_buzzer_init(void)
{
	taskBuzzerNextRun = HAL_GetTick() + TASK_BUZZER_PERIOD_TICKS;
}

void task_buzzer_execute(void)
{
    if (nums.steps >= nums.goal && !buzzerActive) {
        buzzerStartTime = HAL_GetTick();  // Start the buzzer timer
        buzzerActive = true;                 // Set the buzzer as active
    }

    // If the buzzer is active, keep it on for 2 seconds
    if (buzzerActive) {
        if (HAL_GetTick() - buzzerStartTime < 2000) {
            pwm_setDutyCycle(&htim16, TIM_CHANNEL_1, 50);  // Turn on buzzer
        } else {
            pwm_setDutyCycle(&htim16, TIM_CHANNEL_1, 0);   // Turn off buzzer after 2 seconds
                                           // Reset buzzer state
        }
    } else {
        // If the goal is not reached, make sure the buzzer is off
        pwm_setDutyCycle(&htim16, TIM_CHANNEL_1, 0);
    }

    if (nums.steps < nums.goal) {
        buzzerActive = false;  // Reset buzzer when the goal is no longer reached
    }

}

uint32_t getTaskBuzzer(void)
{
	return taskBuzzerNextRun;
}

void setTaskBuzzer(uint32_t nextRunTick)
{
    taskBuzzerNextRun = nextRunTick;
}

void incrementTaskBuzzer(void)
{
	taskBuzzerNextRun += TASK_BUZZER_PERIOD_TICKS;
}

