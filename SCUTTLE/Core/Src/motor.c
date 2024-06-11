/**
 * @file motor.c
 * @brief Motor Driver
 * @details This code allows one to enable/disable and set the duty cycle of a motor
 * @date Created on: Apr 29, 2024
 * @author Nathan Chapman
 * ![](Krabby.png)
 */

#include "motor.h"

/**
 * @brief Set the duty cycle of the motor.
 * @param[in] p_mot Pointer to the motor object structure.
 * @param[in] level Desired duty cycle percentage (-100 to 100).
 * @details This function constrains the level to the valid range and sets the
 * 			PWM duty cycle by updating the compare register pointer directly.
 */
void set_duty(motor_t* p_mot, int32_t level) {
	/// Constrain level to valid range
	if (level > 100) level = 100;
    if (level < -100) level = -100;
	/// Initialize pulse width variables
    uint32_t pulse1 = 0;
    uint32_t pulse2 = 0;
    if(level > 0 ){
    	pulse2 = (uint32_t)((level * p_mot->Period) / 100);
    }
    else if(level < 0){
    	pulse1 = (uint32_t)((-level * p_mot->Period) / 100);
    }
    /// Set the PWM duty cycle by updating the compare register
    *(p_mot->chA) = pulse1;
    *(p_mot->chB) = pulse2;

}
