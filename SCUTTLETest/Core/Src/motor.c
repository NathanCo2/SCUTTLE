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
/**
 * @brief Enable channel A with a specified duty cycle.
 * @param[in] p_mot Pointer to the motor structure.
 * @param[in] level Desired duty cycle level (0 to 100).
 */
void enable_chA(motor_t* p_mot, int32_t level) {
    uint32_t pulse = (uint32_t)((level * p_mot->Period) / 100);
    *(p_mot->chA) = pulse;
}

/**
 * @brief Enable channel B with a specified duty cycle.
 * @param[in] p_mot Pointer to the motor structure.
 * @param[in] level Desired duty cycle level (0 to 100).
 */
void enable_chB(motor_t* p_mot, int32_t level) {
    uint32_t pulse = (uint32_t)((level * p_mot->Period) / 100);
    *(p_mot->chB) = pulse;
}

/**
 * @brief Disable channel A.
 * @param[in] p_mot Pointer to the motor structure.
 */
void disable_chA(motor_t* p_mot) {
    *(p_mot->chA) = 0;
}

/**
 * @brief Disable channel B.
 * @param[in] p_mot Pointer to the motor structure.
 */
void disable_chB(motor_t* p_mot) {
    *(p_mot->chB) = 0;
}

/**
 * @brief Set the duty cycle for channel A.
 * @param[in] p_mot Pointer to the motor structure.
 * @param[in] level Desired duty cycle level (0 to 100).
 */
void set_duty_chA(motor_t* p_mot, int32_t level) {
    uint32_t pulse = (uint32_t)((level * p_mot->Period) / 100);
    *(p_mot->chA) = pulse;
}

/**
 * @brief Set the duty cycle for channel B.
 * @param[in] p_mot Pointer to the motor structure.
 * @param[in] level Desired duty cycle level (0 to 100).
 */
void set_duty_chB(motor_t* p_mot, int32_t level) {
    uint32_t pulse = (uint32_t)((level * p_mot->Period) / 100);
    *(p_mot->chB) = pulse;
}
