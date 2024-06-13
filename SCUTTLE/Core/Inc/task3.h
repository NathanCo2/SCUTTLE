/**
 * @file task3.h
 *
 * @brief Header file for Task 3: OPENMV Camera Interface
 *
 * This file contains the function prototype for the state machine implementing
 * communication with an OPENMV camera via UART.
 *
 * @date Jun 5, 2024
 * @author tawel
 */

#ifndef INC_TASK3_H_
#define INC_TASK3_H_

#include <stdio.h>
#include "stm32l4xx_hal.h"

/**
 * @brief Runs the state machine for the OPENMV Camera interface.
 *
 * This function implements the state machine for interfacing with an OPENMV camera
 * via UART. It manages the process of requesting, receiving, and processing distance
 * and angle data from the camera.
 *
 * @param State Pointer to the state variable of the state machine.
 * @param Distance_Target Pointer to the variable where the target distance will be stored.
 * @param Angle_Target Pointer to the variable where the target angle will be stored.
 * @param SPI_Rec Pointer to the SPI receive flag variable.
 * @param Follow Pointer to the follow mode flag variable.
 * @param OpenMV Pointer to the OPENMV mode flag variable.
 * @param UART3 UART handle for communication with the OPENMV camera.
 */
void task3_run(uint8_t* State, float* Distance_Target, float* Angle_Target, uint8_t* SPI_Rec,
               uint8_t* Follow, uint8_t* OpenMV, UART_HandleTypeDef UART3);

#endif /* INC_TASK3_H_ */
