/*
 * task1.h
 *
 *  Created on: Jun 3, 2024
 *      Author: tawel
 */

#ifndef INC_TASK1_H_
#define INC_TASK1_H_

#include <stdio.h>
#include "stm32l4xx_hal.h"

/**
 * @file task1.h
 * @brief Header file for Task 1 diagnostics test functions.
 * @date June 3, 2024
 * @author tawel
 */

/**
 * @brief Run task 1, which includes diagnostics and battery level check.
 * @param State Pointer to the state variable.
 * @param Analog1 ADC handle for battery level check.
 * @param Kill Pointer to the kill switch variable.
 */
void task1_run(uint8_t* State, ADC_HandleTypeDef Analog1, uint8_t* Kill); // Function prototype declaration

#endif /* INC_TASK1_H_ */
