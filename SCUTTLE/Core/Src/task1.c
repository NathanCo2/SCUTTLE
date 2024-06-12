/*
 * task1.c
 *
 *  Created on: Jun 3, 2024
 *      Author: tawel
 */

//task1.c
//Task 1: diagnostics Test, including battery level check


#include "task1.h"

uint16_t Bat_Res = 0; //Battery reading, should not be below 3303

void task1_run(uint8_t* State, ADC_HandleTypeDef Analog2,uint8_t* Kill) {
    // Task 1 implementation
	while(1){
		switch(*State){

		case 0:
			//State 0: INIT
			//Initialize ADC
			HAL_ADC_Start(&Analog2);
			//Analog2.Init.EOCSelection = DISABLE; //Apparently important
			//Set Variables

			*State = 1;

			break;

		case 1:
			//State 1: Check Battery
			//Read ADC, make sure good for conversion first

			Bat_Res = HAL_ADC_GetValue(&Analog2);
			Bat_Res = HAL_ADC_GetValue(&Analog2); //Have to do it twice i think
			HAL_ADC_Start(&Analog2);

			if (Bat_Res<3303) {
				//If battery too low, turn everything off, they should be on by default
				*Kill = 1; //Kill if battery too low

			}

			*State = 1; //Always return to state 1

			break;

		}



	}

}
