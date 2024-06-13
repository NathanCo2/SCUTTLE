/*
 * Counter.h
 *
 *  Created on: Jun 8, 2024
 *      Author: tawel
 */

#ifndef SRC_COUNTER_H_
#define SRC_COUNTER_H_

#include <stdio.h>
#include "stm32l4xx_hal.h"

/**
 * @file Counter.h
 * @brief Header file for counter operations
 * @date June 8, 2024
 * @author tawel
 */

/**
 * @brief Delay function prototype to wait for a specified number of microseconds.
 * @param Timer Timer handle for the timer used for delay.
 * @param us Microseconds to delay.
 */
void Delay_us(TIM_HandleTypeDef Timer, uint16_t us);

#endif /* SRC_COUNTER_H_ */
