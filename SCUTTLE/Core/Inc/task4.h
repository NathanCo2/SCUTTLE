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

/**
 * @file task4.h
 * @brief Header file for Task 4: Metal Detector functionality.
 * @date June 8, 2024
 * @author tawel
 */

/**
 * @brief Task 4 state machine: Metal Detector.
 *
 * @param State Pointer to the state variable.
 * @param MDON Pointer to the Metal Detector ON status flag.
 * @param sumval Pointer to the summed ADC values, which functions as measure of certainty of metal detected.
 * @param Timer Timer handle for delay functions. (Now Deprecated)
 * @param Metal_Found Pointer to the metal found status flag.
 * @param Analog1 ADC handle for the first ADC channel.
 * @param Analog2 ADC handle for the second ADC channel.
 * @param Analog3 ADC handle for the third ADC channel.
 */
void task4_run(uint8_t* State, uint8_t* MDON, uint32_t* sumval, TIM_HandleTypeDef Timer, uint8_t* Metal_Found, ADC_HandleTypeDef Analog1, ADC_HandleTypeDef Analog2, ADC_HandleTypeDef Analog3);

#endif /* INC_TASK4_H_ */
