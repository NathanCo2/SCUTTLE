/*
 * task4.c
 *
 *  Created on: Jun 8, 2024
 *      Author: tawel
 */
#include "task4.h"
#include <stdlib.h>


//Task 4 state machine: Metal Detector
void task4_run(uint8_t* State){

	while(1){
			switch(*State){

			case 0:
				//State 0: INIT

				*State = 1;

				break;

				void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

					if (MDON ==1){
						// Check which version of the timer triggered this callback
						//Turn on metal detector BJT
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);

						if (htim == &htim6 ){
							switch(TIM6_Stage){

							case 0:
								TIM7->CR1 &= ~TIM_CR1_CEN; //Disable timer 7
								//Read Potentiometer to find delay
								if (HAL_ADC_PollForConversion(&hadc3, 10000) == HAL_OK){
									Delay_MD = HAL_ADC_GetValue(&hadc3);
									HAL_ADC_Start(&hadc3);
									}
								//If we cant read yet, repeat this step
								else{
									TIM6_Stage = 0;
									//Probably want some sort of error message here
									break;
								}


								//Use this delay to Set Timer 7 delay

								TIM7->PSC = (impuls+Delay_MD);
								TIM7->CR1 |= TIM_CR1_CEN; //Re-Enable

								//Go to next statge
								TIM6_Stage = 1;

								//Finally, set metal detector ON
								HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);

								break;

							//The next cases are identical, so allow to fall through
							case 1:
							case 2:
							case 3:
							case 4:
							case 5:
							case 6:
							case 7:
							case 8:
							case 9:
								//Set Pin low and go to next stage
								HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
								TIM6_Stage = TIM6_Stage + 1;
							case 10:
								HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
								TIM6_Stage = 0; //Go back to beginning
								break;



							}


						}
						if (htim == &htim7){
							switch(TIM7_Stage){

							//The next cases are identical
							case 1:
							case 2:
							case 3:
							case 4:
							case 5:
							case 6:
							case 7:
							case 8:
							case 9:
								val[TIM7_Stage-1] = HAL_ADC_GetValue(&hadc1);
								HAL_ADC_Start(&hadc1);
								HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
								TIM7_Stage = TIM7_Stage + 1;
								break;
							case 10:
								val[TIM7_Stage-1] = HAL_ADC_GetValue(&hadc1);
								//Sum all values the boring way
								sumval = val[0]+val[1]+val[2]+val[3]+val[4]+val[5]+val[6]+val[7]+val[8]+val[9];
								sumval = sumval/5;

								base = HAL_ADC_GetValue(&hadc2);
								HAL_ADC_Start(&hadc2);
								if (sumval > base){
									//If we detect metal, act accordingly
									Metal_Found = 1;
									Countdown_Start = 1;
									Countdown_Time = __HAL_TIM_GET_COUNTER(&htim17);//Find EndTime using HAL
									//Turn on Buzzer
									HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
								}
								else{
									if (Countdown_Start == 1){
										//If in count-down phase, check how much time has passed
										//Currently 3 seconds -> 3000ms
										if (GETDELTA(htim17, Countdown_Start, 80000)>3000){

											//If count-down finished, turn off buzzer and say metal not detected
											HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
											Metal_Found = 0;
											Countdown_Start = 0;

										}
									}
									else{
										//Otherwise, make sure buzzer is off
										HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
									}
								}
								//Always return to start
								TIM7_Stage = 1;
								break;
							}

						}

					}
					else{
						sumval = 0;
						//Turn off metal detector module
						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
					}
				}






			}
	}
}

