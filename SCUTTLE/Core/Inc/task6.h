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

/**
 * @file task6.h
 * @brief Header file for Task 6: Drive Motors
 * @date June 10, 2024
 * @author tawel
 */

/**
 * @brief Function to run Task 6 state machine: Drive Motors
 * @param State Pointer to the state variable.
 * @param DriveON_MD Pointer to the variable indicating whether metal is detected.
 * @param DriveON_Rad Pointer to the variable indicating whether radio is triggered.
 * @param Follow Pointer to the variable indicating whether follow mode is active.
 * @param Distance_Target Pointer to the target distance variable.
 * @param Angle_Target Pointer to the target angle variable.
 * @param htim1 Timer handle for motor PWM control.
 * @param htim3 Timer handle for encoder 1.
 * @param htim4 Timer handle for encoder 2.
 */
void task6_run(uint8_t* State, uint8_t* DriveON_MD, uint8_t* DriveON_Rad, uint8_t* Follow, float* Distance_Target, float* Angle_Target,
        TIM_HandleTypeDef htim1, TIM_HandleTypeDef htim3, TIM_HandleTypeDef htim4);

#endif /* SRC_TASK6_H_ */
