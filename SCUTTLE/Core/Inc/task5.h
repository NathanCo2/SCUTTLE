/*
 * task5.h
 *
 *  Created on: Jun 8, 2024
 *      Author: tawel
 */

#ifndef INC_TASK5_H_
#define INC_TASK5_H_

#include <stdio.h>
#include "stm32l4xx_hal.h"


void task5_run(uint8_t* State, uint8_t* ArmON,uint8_t* Metal_Found,TIM_HandleTypeDef Timer,uint32_t* sumval);

#endif /* INC_TASK5_H_ */
