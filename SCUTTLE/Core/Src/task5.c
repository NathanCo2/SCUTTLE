/*
 * task5.c
 *
 *  Created on: Jun 8, 2024
 *      Author: tawel
 */

#include "task5.h"
#include <stdlib.h>
#include "Counter.h"

//Note: 48CPR encoder, 20.4:1 Gear Ratio
float Arm_Encoder_CPR = 979.2; //Number of encoder turns in one revolution
//Probably only want to go between  60 degrees each side -> +- 1/6*Full Rotation
int8_t SweepDeg = 60; //Number of degrees for sweep each side.

float Arm_Pos_Target; //Target position of Arm in encoder ticks

float Arm_Deg_Target; //Target position of Arm in Degrees
float Deg_inc; //Increment of degrees arm

uint16_t Time_Start; //Used to find deltaT

uint8_t TimerStarted = 0; //Used to determine if timer has started

uint8_t S3_First = 0; //Flag to determine if it is the first time through state 3

uint8_t ArmDir = 1; //Arm Direction

float TimeDiff;

uint32_t sumval_old = 0; //Old sumval measurement
uint32_t Metal_Delta; //Difference between old and new metal detector reading

float K_arm = 1; //Arm control Gain value

//Task 5 state machine: Arm Motor
void task5_run(uint8_t* State, uint8_t* ArmON,uint8_t* Metal_Found, TIM_HandleTypeDef Timer, uint32_t* sumval){

	while(1){
			switch(*State){

			case 0:
				//State 0: INIT

				//ZERO ARM ENCODER

				Arm_Pos_Target = 0; //Set passive sweep target to 0
				Arm_Deg_Target = 0; //Set passive sweep target to 0
				Deg_inc = .01; //Set degree increment

				*State = 1;

				break;

			case 1:
				//State 1: Flag check
				if(*ArmON == 1){

					if(*Metal_Found == 1){
						//If metal found, go to state 3
						*State = 3;
					}

					else{
						//If Metal not found, do passive sweep
						*State = 2;
						sumval_old = *sumval; //Reset metal detector sumval
						//Get current time if needed
						if (TimerStarted == 0){
							Time_Start = __HAL_TIM_GET_COUNTER(&Timer);//Find EndTime using HAL
							TimerStarted = 1;
						}
					}
				}

				else{
					//If Arm not enabled, turn off motor and return to state 1

					//SET ARM MOTOR TO ZERO DUTY CYCLE

					*State = 1;
				}

				break;

			case 2:
				//State 2: Passive Arm Movement

				//SET TARGET ENCODER VALUE


				//Get current time difference, if it is greater than or equal to 10ms, then set new arm target.
				TimeDiff = GETDELTA(Timer, Time_Start, 80000);
				if (TimeDiff >= 10){
					//If 10ms have passed, update arm position target

					if (abs(Arm_Deg_Target) >= SweepDeg){
						//If we have gone past our max degrees, then change direction
						Deg_inc = -Deg_inc;
					}

					//Set new Target in degrees
					Arm_Deg_Target = Arm_Deg_Target + Deg_inc;

							//Convert to desired encoder position
					Arm_Pos_Target = Arm_Deg_Target/360*Arm_Encoder_CPR;

					TimerStarted = 0; //Reset Timer

					//Note on this implementation: The target changes as a ramp function over time, so there is potential to overshoot
					//or other weird behavior. This should be tested fully before full implementation.



				}

				//It may also be prudent to turn the arm off if we read an encoder reading that is greater than 90 degrees

				//ESTOP If encoder reads over 90 degrees

				//READ ENCODER

				//if (abs(reading/Arm_Encoder_CPR*360)>=90)   {
					//*ArmON = 0;
					//}

				*State = 1; //Always return to state 1

				break;

			case 3:
				//State 3: Control algorithm to find metal.
				if (S3_First == 1){
					S3_First = 0; //Dont go through this loop again
					Arm_Deg_Target = Arm_Deg_Target + Deg_inc; //Try going one way first
					Arm_Pos_Target = Arm_Deg_Target/360*Arm_Encoder_CPR;
					Time_Start = __HAL_TIM_GET_COUNTER(&Timer);//Find EndTime using HAL
					sumval_old = *sumval;
				}

				else{
					TimeDiff = GETDELTA(Timer, Time_Start, 80000);
					if (TimeDiff >= 10){
						//If 10ms have passed, update arm position target
						Metal_Delta = *sumval-sumval_old;
						Time_Start = __HAL_TIM_GET_COUNTER(&Timer);//Find EndTime using HAL
						if (Metal_Delta < 0){
							//If we moved away from the metal detection, reverse direction
							ArmDir = -ArmDir; //Reverse arm direction
						}
						//I think this code tries to make the Delta = 0
						Arm_Pos_Target = Arm_Pos_Target + K_arm*ArmDir*abs(Metal_Delta);
						sumval_old = *sumval;
					}


				}





				//Set to max If encoder reads over 90 degrees

				//READ ENCODER

				//if (abs(reading/Arm_Encoder_CPR*360)>=90)   {
					//Arm_Pos_Target = 0;
					//*State = 1;
					//if (reading<0){
						//Arm_Deg_Target = -90; //Set max to negative 90
						//Arm_Pos_Target = Arm_Deg_Target/360*Arm_Encoder_CPR;
					//}

					//else{
						//Arm_Deg_Target = 90; //Set max to positive 90
						//Arm_Pos_Target = Arm_Deg_Target/360*Arm_Encoder_CPR;
					//}

				//SET ENCODER TARGET VALUE

				if(*Metal_Found == 0){
					//Arm_Dir = 1; //Reset Arm Direction
					*State = 1; //Return to State 1
				}

			}

				break;
	}
}

