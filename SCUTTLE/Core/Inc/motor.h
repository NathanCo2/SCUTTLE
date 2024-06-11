/**
 * @file motor.h
 * @brief Motor Driver Header File
 * @details This header file contains the declarations for the motor driver functions
 * and the motor_t structure.
 * @date Created on: Apr 29, 2024
 * @author Nathan Chapman
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "stm32l4xx_hal.h"
#include <stdint.h>

/// @brief Motor object data structure.
typedef struct {
    volatile uint32_t* chA; ///< Pointer to the CCR for the first timer channel.
    volatile uint32_t* chB; ///< Pointer to the CCR for the second timer channel.
    uint32_t Period;         ///< Auto reload value to properly set duty cycle percentage.
} motor_t;

// Function prototypes for motor control
void set_duty(motor_t* p_mot, int32_t level);


#endif /* INC_MOTOR_H_ */
