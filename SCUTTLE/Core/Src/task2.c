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


void task2_run(uint8_t* State, uint8_t* BatKill,uint8_t* RadKill,uint16_t* usWidth)
{
    // Task 2 implementation
	while(1){
		switch(*State){

		case 0:
			//State 0: INIT

			*State = 1;

		case 1:
			//State 1: Check Battery
			//Check Radio First, then Battery
			if(abs(*usWidth-1500)<200) //If Pulse width within 200 microseconds, then kill
			{
				*RadKill = 1;
				//Kill all motors and metal detector
			}
			else {
				*RadKill = 0;
				}

			if (*BatKill == 1){
				//Kill Everything

			}
			*State = 1; //Always return to state 1

		}



	}

}
