/**
 * @file motorcontrol.c
 * @brief Motor Controller
 * @details Requires working encoder and motor driver. Implements PID control to drive motor
 * @date Created on: June 5, 2024
 * @author Nathan Chapman
 */

#include "motorcontrol.h"

/**
 * @brief Read encoder value
 * @param[in] controller A pointer to a structure (controller_t) containing controller gains and relevant information
 * @param[in] motor A pointer to a structure (motor_t) containing motor data
 * @param[in] encoder A pointer to a structure (encoder_t) containing encoder-related data such as position, velocity, and the last counter value.
 * @details This function runs the motor controller loop that alters motor duty cycle to reach a position or velocity setpoint
 */
void run_control(controller_t *controller, motor_t *motor, encoder_t *encoder) {
	// Read the current position and velocity from the encoder
	read_encoder(encoder);

	// Calculate the error
	int32_t error = controller->velocity_setpoint - encoder->velocity;

	// Integral term calculation
	controller->esum += error;

	// Calculate the duty cycle
	float duty = controller->Pgain_velocity * error + controller->Igain_velocity * controller->esum;
//	printf("Duty sent: %ld\n", (long)duty); // For debug

	// Apply to the motor
	set_duty(motor, duty);


}
