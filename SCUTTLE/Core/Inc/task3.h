/*
 * task3.h
 *
 *  Created on: Jun 5, 2024
 *      Author: tawel
 */

#ifndef INC_TASK3_H_
#define INC_TASK3_H_

#include <stdio.h>
#include "stm32l4xx_hal.h"


void task3_run(uint8_t* State,float* Distance_Target,float* Angle_Target,uint8_t* SPI_Rec,
		uint8_t* Follow,uint8_t* OpenMV,UART_HandleTypeDef UART3);

#endif /* INC_TASK3_H_ */
