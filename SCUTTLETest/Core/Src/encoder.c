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
 * @param[in] p_mot Pointer to the motor object structure.
 * @param[in] level Desired duty cycle percentage (-100 to 100).
 * @details This function constrains the level to the valid range and sets the
 * 			PWM duty cycle by updating the compare register pointer directly.
 */
void read_encoder(encoder_t *encoder_value, TIM_HandleTypeDef *htim) {
	uint32_t temp_counter = __HAL_TIM_GET_COUNTER(htim); //temp_counter = current encoder timer value
	static uint8_t first_time = 0;
	if(!first_time) //initialize
	{
	   encoder_value ->velocity = 0; //set velocity zero
	   first_time = 1;
	}
	else
	{
	  if(temp_counter == encoder_value ->last_counter_value)
	  {
	    encoder_value ->velocity = 0;
	  }
	  else if(temp_counter > encoder_value ->last_counter_value)
	  {
	    if (__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))
	    {
	      encoder_value ->velocity = -encoder_value ->last_counter_value -
		(__HAL_TIM_GET_AUTORELOAD(htim)-temp_counter);
	    }
	    else
	    {
	      encoder_value ->velocity = temp_counter -
	           encoder_value ->last_counter_value;
	    }
	  }
	  else
	  {
	    if (__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))
	    {
		encoder_value ->velocity = temp_counter -
	            encoder_value ->last_counter_value;
	    }
	    else
	    {
		encoder_value ->velocity = temp_counter +
		(__HAL_TIM_GET_AUTORELOAD(htim) -
	              encoder_value ->last_counter_value);
	    }
	   }
	}
	encoder_value ->position += encoder_value ->velocity;
	encoder_value ->last_counter_value = temp_counter;
	 }
