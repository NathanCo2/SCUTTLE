/*
 * task6.h
 *
 *  Created on: Jun 10, 2024
 *      Author: tawel
 */

#ifndef SRC_TASK6_H_
#define SRC_TASK6_H_

#include <stdio.h>
#include "stm32l4xx_hal.h"


void task6_run(uint8_t* State,uint8_t* DriveON_MD,uint8_t* DriveON_Rad,uint8_t* Follow, float* Distance_Target, float* Angle_Target);

#endif /* SRC_TASK6_H_ */
