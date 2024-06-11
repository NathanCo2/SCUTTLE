/**
 * @file encoder.h
 * @brief encoder Header File
 * @details This header file contains the declarations for the encoder driver functions
 * and the encoder_t structure. Resource: https://www.steppeschool.com/pages/blog/stm32-timer-encoder-mode
 * @date Created on: June 3, 2024
 * @author Nathan Chapman
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include "stm32l4xx_hal.h"
#include <stdint.h>

/// @brief Encoder object data structure.
/// @brief Encoder object data structure.
typedef struct{
	TIM_HandleTypeDef *htim; ///< Timer handle used for reading the counter value
    int16_t velocity;
    int32_t position;
    uint32_t last_counter_value;
    uint32_t last_tick;
} encoder_t; // encoder instance

// Function prototypes for encoder
void read_encoder(encoder_t *encoder);


#endif /* INC_ENCODER_H_ */
