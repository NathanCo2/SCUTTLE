/*
 * task6.c
 *
 *  Created on: Jun 10, 2024
 *      Author: tawel
 */
#include "task6.h"
#include <stdlib.h>
#include "motorcontrol.h"
#include "encoder.h"

//Task 6 state machine: Drive Motors
void task6_run(uint8_t* State, uint8_t* DriveON_MD,uint8_t* DriveON_Rad,uint8_t* Follow, float* Distance_Target, float* Angle_Target, TIM_HandleTypeDef htim1,TIM_HandleTypeDef htim3,TIM_HandleTypeDef htim4){

	while(1){
			switch(*State){

			case 0:
				//State 0: INIT

				uint32_t previousMillis = 0;//for debug

				// Motor and encoder instances
				motor_t motor1;
				motor_t motor2;
				encoder_t encoder1;
				encoder_t encoder2;
				controller_t controller1;
				controller_t controller2;

				// Assign motor 1 to Timer 1 channels 1 and 3
				motor1.chA = &(htim1.Instance->CCR2);
				motor1.chB = &(htim1.Instance->CCR4);
				motor1.Period = __HAL_TIM_GET_AUTORELOAD(&htim1);

				// Assign motor 2 to Timer 1 channels 2 and 4
				motor2.chA = &(htim1.Instance->CCR1);
				motor2.chB = &(htim1.Instance->CCR3);
				motor2.Period = __HAL_TIM_GET_AUTORELOAD(&htim1);

				//Set initial duty cycles
				set_duty(&motor1, 0);
				set_duty(&motor2, 0);

				// Initialize encoders
				int16_t mot1_velocity = 0;
				int32_t mot1_position = 0;
				uint32_t enc1_lastval = 0;
				uint32_t last_tick1 = 0;
				encoder1 = (encoder_t){&htim3, mot1_velocity, mot1_position, enc1_lastval, last_tick1};

				int16_t mot2_velocity = 0;
				int32_t mot2_position = 0;
				uint32_t enc2_lastval = 0;
				uint32_t last_tick2 = 0;
				encoder2 = (encoder_t){&htim4, mot2_velocity, mot2_position, enc2_lastval, last_tick2};

				//Set test duty cycles
				set_duty(&motor1, 0);
				set_duty(&motor2, 0);

				// Initialize controllers
				float Pgain_velocity1 = 0.04;
				float Igain_velocity1 = 0.01;
				int32_t velocity_setpoint1 = 0;
				int32_t esum1 = 0;
				controller1 = (controller_t){Pgain_velocity1, Igain_velocity1, velocity_setpoint1, esum1};

				float Pgain_velocity2 = 0.04;
				float Igain_velocity2 = 0.01;
				int32_t velocity_setpoint2 = 0;
				int32_t esum2 = 0;
				controller2 = (controller_t){Pgain_velocity2, Igain_velocity2, velocity_setpoint2, esum2};


				float Pgain_distance = 500; //how much to scale velocity based on distance away
				//float angle_error; // updated by open mv H7 camera
				float Pgain_angle = 4000;//0.6; //how much to scale skid steering based on angle error
				float skid_modifier; // how much to scale motor setpoints to achieve angle turn

				//Setup follow variables
				//int32_t current_distance; //updated by open mv H7 camera
				float distance_error = 0;
				float velocity_setpoint = 0;
				float optimal_distance = -11; // desired follow distance

				float max_skid_modifier = 1.0; // Adjust this value as needed
				float max_velocity = 3000;
				*State = 1;

				break;


			case 1:
				//State 1: Flag check
				if (*DriveON_Rad == 1){
					//If radio triggered, run rest of code
					if (*DriveON_MD == 1){
						//If Metal Detected, Go to state 3
						*State = 3;
					}
					else{
						//Otherwise, go to follow mode
						if (*Follow == 1){
							*State = 2;
						}

						else{
							*State = 4;
							//DEBUG STATE
						}
					}
				}

				else{
					*State = 1; //Else, return to state 1

					//SET DRIVE MOTORS TO 0;
				}

				break;

			case 2:
				//State 2: Follow mode


				if(*Distance_Target != 0){
					distance_error = *Distance_Target - optimal_distance;

				velocity_setpoint = -distance_error*Pgain_distance;
				if (velocity_setpoint > max_velocity) {
					velocity_setpoint = max_velocity;
					} else if (velocity_setpoint < -max_velocity) {
						velocity_setpoint = -max_velocity;
					}
				skid_modifier = Pgain_angle*(*Angle_Target+0.09);


				// Cap the skid modifier to avoid useless values

//				if (skid_modifier > max_skid_modifier) {
//				    skid_modifier = max_skid_modifier;
//				    } else if (skid_modifier < -max_skid_modifier) {
//				        skid_modifier = -max_skid_modifier;
//				    }
//
//					// Turn
//					controller1.velocity_setpoint = velocity_setpoint * (1 + skid_modifier);
//					controller2.velocity_setpoint = velocity_setpoint * (1 - skid_modifier);

				controller1.velocity_setpoint = velocity_setpoint  + skid_modifier;
				controller2.velocity_setpoint = velocity_setpoint  - skid_modifier;
				}
				else{
					controller1.velocity_setpoint = 0;
					controller2.velocity_setpoint = 0;
				}



				if (HAL_GetTick() - previousMillis >= 100) {
					previousMillis = HAL_GetTick();

			        // Print velocities
//					printf("Angle: %ld\n", (int)Angle_Target);
//			        printf("Velocity1: %ld\n", controller1.velocity_setpoint);
//			        printf("Velocity2: %ld\n", controller2.velocity_setpoint);
			        run_control(&controller1, &motor1, &encoder1);
			        run_control(&controller2, &motor2, &encoder2);
			    }



				*State = 1; //Always return to State 1
				break;



			case 3:
				//State 3: Metal Detected Mode

				//SET ALL MOTORS TO BRAKE MODE
				controller1.velocity_setpoint = 0;
				controller2.velocity_setpoint = 0;

				run_control(&controller1, &motor1, &encoder1);
				run_control(&controller2, &motor2, &encoder2);

				//Could add additional drive forward and backward functionality here
				//But for demo, we have simplified the design

				*State = 1; //Always return to State 1

				break;



			case 4:
				//State 4: DEBUG Testing, should be empty on final code
				*State = 1; //Always return to State 1
				if (HAL_GetTick() - previousMillis >= 100) {
						  previousMillis = HAL_GetTick();
						  controller1.velocity_setpoint = 100000;
						  run_control(&controller1, &motor1, &encoder1);
//						  controller2.velocity_setpoint = 100000;
//						  run_control(&controller2, &motor2, &encoder2);

	//		  	          read_encoder(&encoder1);
	//		  	          read_encoder(&encoder2);
			  	    	  printf("Encoder1 position: %ld\n", encoder1.position);
			  	    	  printf("Encoder1 Velocity: %d\n", encoder1.velocity);
//						  printf("Encoder2 position: %ld\n", encoder2.position);
//						  printf("Encoder2 Velocity: %d\n", encoder2.velocity);
				}
				break;




			}
	}

}

