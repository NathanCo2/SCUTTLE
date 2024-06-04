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
 * @param[in] encoder_p A pointer to a structure (encoder_t) containing encoder-related data such as position, velocity, and the last counter value.
 * @param[in] htim A pointer to the timer handle used to read the counter value.
 * @details This function constrains the level to the valid range and sets the
 * 			PWM duty cycle by updating the compare register pointer directly.
 */
void read_encoder(encoder_t *encoder_p, TIM_HandleTypeDef *htim) {
	uint32_t temp_counter = __HAL_TIM_GET_COUNTER(htim); //temp_counter = current encoder timer value
	static uint8_t first_time = 0;
	if(!first_time) //initialize
	{
	   encoder_p ->velocity = 0; //set velocity zero
	   first_time = 1;
	}
	else
	{
	  if(temp_counter == encoder_p ->last_counter_value) //if counter is unchanged, set velocity to 0
	  {
	    encoder_p ->velocity = 0;
	  }
	  else if(temp_counter > encoder_p ->last_counter_value) //if counter is larger than last
	  {
	    if (__HAL_TIM_IS_TIM_COUNTING_DOWN(htim)) //account for scenario in which count is decreasing
	    {
	      encoder_p ->velocity = -(encoder_p ->last_counter_value) - (__HAL_TIM_GET_AUTORELOAD(htim)-temp_counter);
	    }
	    else
	    {
	      encoder_p ->velocity = temp_counter - (encoder_p ->last_counter_value);
	    }
	  }
	  else
	  {
	    if (__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))
	    {
		encoder_p ->velocity = temp_counter - encoder_p ->last_counter_value;
	    }
	    else
	    {
		encoder_p ->velocity = temp_counter + (__HAL_TIM_GET_AUTORELOAD(htim) - (encoder_p ->last_counter_value));
	    }
	   }
	}
	encoder_p ->position += encoder_p ->velocity;
	encoder_p ->last_counter_value = temp_counter;
	 }
