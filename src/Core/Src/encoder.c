/**
 * @file encoder.c
 * @brief Encoder Driver
 * @details This code allows the user to read and update encoder values
 * @date Created on: June 3, 2024
 * @author Nathan Chapman
 */

#include "encoder.h"

/**
 * @brief Read encoder value
 * @param[in] encoder A pointer to a structure (encoder_t) containing encoder-related data such as position, velocity, and the last counter value.
 * @param[in] htim A pointer to the timer handle used to read the counter value.
 * @details This function reads a timer setup in encoder mode and finds position and velocity, accounting for overflow and direction change.
 */
void read_encoder(encoder_t *encoder) {

	//initialize internal variables
    uint32_t current_counter = __HAL_TIM_GET_COUNTER(encoder->htim); //Inverted due to wiring
    int32_t velocity_change;
    float delta_t;
    float current_tick = HAL_GetTick();

	// Calculate velocity change
	if (current_counter >= encoder->last_counter_value) {
		velocity_change = current_counter - encoder->last_counter_value; //Velocity has units of counts per timer tick
	} else {
		velocity_change = __HAL_TIM_GET_AUTORELOAD(encoder->htim) - encoder->last_counter_value + current_counter;
		if (!__HAL_TIM_IS_TIM_COUNTING_DOWN(encoder->htim)) { //If encoder is rotating in other direction
			velocity_change *= -1; // Invert for counting down mode
		}
	}
	// Update position and store last counter value
	encoder->position += velocity_change;
	encoder->last_counter_value = current_counter;

	delta_t = (current_tick > encoder->last_tick) ? ((current_tick - encoder->last_tick)/1000) : 1; //how much time(ms) elapsed since last run
    encoder->velocity = (int16_t)(velocity_change / delta_t); //units of encoder counts / s
    encoder->last_tick = current_tick;


}
