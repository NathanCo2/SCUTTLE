/*
 * task6.c
 *
 *  Created on: Jun 10, 2024
 *      Author: tawel
 */
#include "task6.h"
#include <stdlib.h>

//Task 6 state machine: Drive Motors
void task6_run(uint8_t* State, uint8_t* DriveON_MD,uint8_t* DriveON_Rad,uint8_t* Follow, float* Distance_Target, float* Angle_Target){

	while(1){
			switch(*State){

			case 0:
				//State 0: INIT

				*State = 1;

				break;


			case 1:
				//State 1: Flag check
				if (*DriveON_Rad == 1){
					//If radio triggered, run rest of code
					if (*DriveON_MD == 0){
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
