/*
 * task3.c
 *
 *  Created on: Jun 5, 2024
 *      Author: tawel
 */


#include "task3.h"
#include <stdlib.h>

//Initialize in-task variables
uint8_t Buffer[4]; //Buffer received via SPI
int16_t Distance_Int; //Distance received
int16_t Angle_Int; //Angle received

uint8_t Req = 0; //Requesting SPI

//Task 3 state machine: OPENMV Camera
void task3_run(uint8_t* State,float* Distance_Target,float* Angle_Target,uint8_t* SPI_Rec,
		uint8_t* Follow,uint8_t* OpenMV,SPI_HandleTypeDef SPI_3){

	while(1){
			switch(*State){

			case 0:
				//State 0: INIT

				*State = 1;
				break;

			case 1:
				//State 1: Flag Check

				//If we are in follow mode and OpenMV mode, then
				if((*Follow==1)&&(*OpenMV==1)){
					if(*SPI_Rec==0){
						if (Req == 0){
							//If we have not requested data yet, request
							*State = 2; //Next State Receive Data
						}
						else{
							*State = 1; //Otherwise stay in this state
						}

					}
					else{
						*State = 3; //If we already received data, process it
					}
				}
				else{
					*State = 1;
				}

				break;

			case 2:
				//State 2: Receive Data
				HAL_SPI_Receive_IT(&SPI_3, Buffer, 4);
				Req = 1;

				*State = 1; //Go back to flag check and wait for receive

				break;


			case 3:
				//State 3: Process Data
				//Convert buffer data to ints. First part of buffer should be distance, second part angle
				Distance_Int = (int16_t)(Buffer[0] << 8 | Buffer[1]);
			    Angle_Int = (int16_t)(Buffer[2] << 8 | Buffer[3]);

				// Convert to float (assuming the data was sent as 16-bit floats)
				*Distance_Target = (float)Distance_Int;
				*Angle_Target = (float)Angle_Int;

				//Once data is fully processed, return to state 1 and reset recieve flag
				*SPI_Rec = 0;
				*State = 1;
				Req = 0; //Reset Request

				break;


			}
	}


}
