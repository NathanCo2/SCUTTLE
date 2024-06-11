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
void task6_run(uint8_t* State, uint8_t* DriveON_MD,uint8_t* DriveON_Rad,uint8_t* Follow, float* Distance_Target, float* Angle_Target){

	while(1){
			switch(*State){

			case 0:
				//State 0: INIT

				float Pgain_distance = 0.5; //how much to scale velocity based on distance away
				//float angle_error; // updated by open mv H7 camera
				float Pgain_angle = 0.5; //how much to scale skid steering based on angle error
				float skid_modifier; // how much to scale motor setpoints to achieve angle turn

				//Setup follow variables
				//int32_t current_distance; //updated by open mv H7 camera
				float distance_error;
				float velocity_setpoint;
				float optimal_distance; // desired follow distance


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



				distance_error = *Distance_Target - optimal_distance;
				velocity_setpoint = distance_error*Pgain_distance;

				skid_modifier = Pgain_angle*(*Angle_Target);


				// Cap the skid modifier to avoid useless values
				float max_skid_modifier = 1.0; // Adjust this value as needed

				if (skid_modifier > max_skid_modifier) {
				    skid_modifier = max_skid_modifier;
				    } else if (skid_modifier < -max_skid_modifier) {
				        skid_modifier = -max_skid_modifier;
				    }


				if (*Angle_Target < 0) {
					// Turn left
					motorcontrol1->velocity_setpoint = velocity_setpoint * (1 + skid_modifier);
					motorcontrol2->velocity_setpoint = velocity_setpoint * (1 - skid_modifier);
			        }
				else {
					// Turn right
					motorcontrol1->velocity_setpoint = velocity_setpoint * (1 - skid_modifier);
					motorcontrol2->velocity_setpoint = velocity_setpoint * (1 + skid_modifier);


				break;



			case 3:
				//State 3: Metal Detected Mode

				//SET ALL MOTORS TO BRAKE MODE

				//Could add additional drive forward and backward functionality here
				//But for demo, we have simplified the design

				*State = 1; //Always return to State 1

				break;



			case 4:
				//State 4: DEBUG Testing, should be empty on final code
				*State = 1; //Always return to State 1

				break;




			}
	}
}
