/*
 * Counter.c
 *
 *  Created on: Jun 8, 2024
 *      Author: tawel
 */

#include "Counter.h"

/**
 * @file Counter.c
 * @brief Implementation file for counter operations
 * @date June 8, 2024
 * @author tawel
 */

uint16_t ElapsedTime;  /**< Elapsed time variable */
float T_ms;             /**< Time in milliseconds */
uint16_t EndTime;       /**< End time variable */

/**
 * @brief Delay function to wait for a specified number of microseconds.
 * @param Timer Timer handle for the timer used for delay.
 * @param us Microseconds to delay.
 */
void Delay_us(TIM_HandleTypeDef Timer, uint16_t us) {
    __HAL_TIM_SET_COUNTER(&Timer, 0);  // Reset the timer counter
    while (__HAL_TIM_GET_COUNTER(&Timer) < us);  // Wait until the timer counter reaches the specified microseconds
}
