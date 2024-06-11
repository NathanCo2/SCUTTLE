/*
 * task2.h
 *
 *  Created on: Jun 3, 2024
 *      Author: tawel
 */

#ifndef INC_TASK2_H_
#define INC_TASK2_H_

#include <stdio.h>
#include "stm32l4xx_hal.h"

void task2_run(uint8_t* State, uint8_t* BatKill,uint8_t* RadKill,int* usWidth,
		uint8_t* DriveON,uint8_t* ArmON,uint8_t* MDON,uint8_t* OPENMV); // Function prototype declaration


#endif /* INC_TASK2_H_ */
