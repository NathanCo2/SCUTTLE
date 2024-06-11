/*
 * task4.h
 *
 *  Created on: Jun 8, 2024
 *      Author: tawel
 */

#ifndef INC_TASK4_H_
#define INC_TASK4_H_

#include <stdio.h>
#include "stm32l4xx_hal.h"


void task4_run(uint8_t* State,uint8_t* MDON, uint32_t* sumval,TIM_HandleTypeDef Timer,uint8_t* Metal_Found,ADC_HandleTypeDef Analog1,ADC_HandleTypeDef Analog2,ADC_HandleTypeDef Analog3);

#endif /* INC_TASK4_H_ */
