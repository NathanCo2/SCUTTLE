/**
 * @file task5.h
 * @brief Header file for Task 5: Arm Motor Control based on Metal Detection
 * @date June 8, 2024
 * @author tawel
 */

#ifndef INC_TASK5_H_
#define INC_TASK5_H_

#include <stdio.h>
#include "stm32l4xx_hal.h"

/**
 * @brief Run task 5, controlling the arm motor based on metal detection and operational state.
 * @param State Pointer to the state variable.
 * @param ArmON Pointer to the variable indicating whether the arm motor is enabled.
 * @param Metal_Found Pointer to the variable indicating whether metal is detected.
 * @param Timer Timer handle for timing operations.
 * @param sumval Pointer to the variable storing the sum value from metal detection.
 */
void task5_run(uint8_t* State, uint8_t* ArmON, uint8_t* Metal_Found, TIM_HandleTypeDef Timer, uint32_t* sumval);

#endif /* INC_TASK5_H_ */
