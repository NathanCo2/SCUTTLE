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

/**
 * @file task2.h
 * @brief Header file for Task 2 functions.
 * @date June 3, 2024
 * @author tawel
 */

/**
 * @brief Run task 2, which includes checking the radio killswitch and activating the metal detector.
 * @param State Pointer to the state variable.
 * @param BatKill Pointer to the battery kill switch flag.
 * @param RadKill Pointer to the radio kill switch flag.
 * @param usWidth Pointer to the pulse width flag.
 * @param DriveON Pointer to the drive system status flag.
 * @param ArmON Pointer to the arm system status flag.
 * @param MDON Pointer to the metal detector on/off flag.
 * @param OPENMV Pointer to the OpenMV camera status flag.
 */
void task2_run(uint8_t* State, uint8_t* BatKill, uint8_t* RadKill, int* usWidth,
               uint8_t* DriveON, uint8_t* ArmON, uint8_t* MDON, uint8_t* OPENMV);

#endif /* INC_TASK2_H_ */
