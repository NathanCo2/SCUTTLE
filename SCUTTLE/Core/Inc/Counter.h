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


float GETDELTA(TIM_HandleTypeDef Timer, uint16_t StartTime, uint32_t Speed_hz);

#endif /* SRC_COUNTER_H_ */
