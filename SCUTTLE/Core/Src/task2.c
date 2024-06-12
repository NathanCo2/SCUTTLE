/*
 * task2.c
 *
 *  Created on: Jun 3, 2024
 *      Author: tawel
 */

//task2.c
//Task 2: Check Radio Killswitch and Metal Detector Activiation


#include "task2.h"
#include <stdlib.h>


void task2_run(uint8_t* State, uint8_t* BatKill,uint8_t* RadKill,int* usWidth,uint8_t* DriveON,uint8_t* ArmON,uint8_t* MDON,uint8_t* OPENMV)
{
    // Task 2 implementation
	while(1){
		switch(*State){

		case 0:
			//State 0: INIT

			*State = 1;

			break;

		case 1:
			//State 1: Check Battery
			//Check Radio First, then Battery
			//Suposed to be 1500, max plus minus 400
			if((abs(*usWidth-1950)>200)&(*usWidth>500)) //If Pulse width within 200 microseconds, then kill
			{
				*RadKill = 1;
				//Kill all motors and metal detector
				*DriveON = 0;
				*ArmON = 0;
				*MDON = 0;
			}
			else {
				*RadKill = 0;
				//Turn on Metal Detector, motors
				*DriveON = 1;
				*ArmON = 1;
				*MDON = 1;
				}

			if (*BatKill == 1){
				//Kill Everything
				*DriveON = 0;
			    *ArmON = 0;
				*MDON = 0;
				*OPENMV = 0;

			}
			*State = 1; //Always return to state 1
			printf("%d\r\n",*usWidth);
			break;

		}



	}

}
