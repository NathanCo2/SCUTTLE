/*
 * motorcontrol.h
 *
 *  Created on: Jun 5, 2024
 *      Author: natha
 */

#ifndef INC_MOTORCONTROL_H_
#define INC_MOTORCONTROL_H_

#include "motor.h"
#include "encoder.h"

/// @brief Controller object data structure.
typedef struct{
	float Pgain_velocity;
	int32_t velocity_setpoint;
	//int32_t last_error;
}controller_t; //controller instance

// Function prototypes
void run_control(controller_t *controller, motor_t *motor, encoder_t *encoder);

#endif /* INC_MOTORCONTROL_H_ */
