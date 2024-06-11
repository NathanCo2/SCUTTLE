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

void Delay_us(TIM_HandleTypeDef Timer,uint16_t us){

	__HAL_TIM_SET_COUNTER(&Timer,0);  // set the counter value a 0
	while (__HAL_TIM_GET_COUNTER(&Timer) < us);  // wait for the counter to reach the us input in the parameter

}
