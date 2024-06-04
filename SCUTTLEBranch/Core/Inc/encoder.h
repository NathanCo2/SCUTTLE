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
typedef struct{
	int16_t velocity;
	int64_t position;
	uint32_t last_counter_value;
}encoder_t; //encoder instance

// Function prototypes for encoder
void read_encoder(encoder_t *encoder_value, TIM_HandleTypeDef *htim);


#endif /* INC_ENCODER_H_ */
