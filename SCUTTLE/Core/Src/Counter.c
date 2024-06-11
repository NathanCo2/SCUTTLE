/*
 * Counter.c
 *
 *  Created on: Jun 8, 2024
 *      Author: tawel
 */


#include "Counter.h"

uint16_t ElapsedTime;
float T_ms;
uint16_t EndTime;

float GETDELTA(TIM_HandleTypeDef Timer,uint16_t StartTime, uint32_t Speed_hz){

	EndTime = __HAL_TIM_GET_COUNTER(&Timer);//Find EndTime using HAL
	// Calculate the elapsed time
	if (EndTime >= StartTime) {
	   ElapsedTime = EndTime - StartTime;
	}
	else {
	    // Handle timer overflow
	    ElapsedTime = (0xFFFFFFFF - StartTime) + EndTime + 1;
	    }

	T_ms = ElapsedTime/Speed_hz*1000; //Find time in Ms
	return T_ms;

}
