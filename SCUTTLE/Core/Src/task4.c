/*
 * task4.c
 *
 *  Created on: Jun 8, 2024
 *      Author: tawel
 */

#include "task4.h"
#include <stdlib.h>
#include "Counter.h"

/**
 * @file task4.c
 * @brief Task 4: Metal Detector.
 *
 * This file contains the implementation for the metal detector. Quick pulses are sent and the resulting
 * analog voltage reading is measured and compared to an adjustable base value. The delay between pulses is
 * also adjustable.
 * @date June 8, 2024
 * @author tawel
 */

/**
 * @brief Adjustable base value to compare to metal detector measurement.
 */
uint16_t base = 0;

/**
 * @brief Signifies time before next metal detection.
 */
uint8_t Countdown_Start = 0;

/**
 * @brief Countdown time for metal detection.
 */
uint16_t Countdown_Time;

/**
 * @brief Array to store ADC values.
 */
uint16_t val[9];

/**
 * @brief Impulse microsecond delay, fixed value.
 */
uint16_t impuls = 120;

/**
 * @brief Adjustable delay for Metal Detector.
 */
uint16_t Delay_MD;

int i;

/**
 * @brief Task 4 state machine: Metal Detector.
 *
 * @param State Pointer to the state variable.
 * @param MDON Pointer to the Metal Detector ON status flag.
 * @param sumval Pointer to the summed ADC values, which functions as measure of certainty of metal detected.
 * @param Timer Timer handle for delay functions. (Now Deprecated)
 * @param Metal_Found Pointer to the metal found status flag.
 * @param Analog1 ADC handle for the first ADC channel.
 * @param Analog2 ADC handle for the second ADC channel.
 * @param Analog3 ADC handle for the third ADC channel.
 */
void task4_run(uint8_t* State, uint8_t* MDON, uint32_t* sumval, TIM_HandleTypeDef Timer, uint8_t* Metal_Found, ADC_HandleTypeDef Analog1, ADC_HandleTypeDef Analog2, ADC_HandleTypeDef Analog3) {
    while (1) {
        switch (*State) {
            case 0:
                // State 0: INIT
                *State = 1;
                break;

            case 1:
                if (*MDON == 1) {
                    // Turn on metal detector BJT
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
                    *State = 2; // Go to state 2
                } else {
                    *sumval = 0;
                    // Turn off metal detector module
                    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
                }
                break;

            case 2:
                // Read Potentiometer to find delay
                if (HAL_ADC_PollForConversion(&Analog3, 10000) == HAL_OK) {
                    Delay_MD = HAL_ADC_GetValue(&Analog3);
                    HAL_ADC_Start(&Analog3);
                } else {
                    // Probably want some sort of error message here
                    break;
                }
                // Set metal detector ON
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);

                for (i = 0; i < 9; i++) {
                    // Delay fixed amount of microseconds
                    Delay_us(Timer, impuls);
                    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
                    // Delay adjustable amount
                    Delay_us(Timer, Delay_MD);
                    // Read a value from ADC
                    val[0] = HAL_ADC_GetValue(&Analog1);
                    HAL_ADC_Start(&Analog1);
                    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
                }

                // Delay fixed amount of microseconds
                Delay_us(Timer, impuls);
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
                // Delay adjustable amount
                Delay_us(Timer, Delay_MD);
                // Read a value from ADC
                val[9] = HAL_ADC_GetValue(&Analog1);
                HAL_ADC_Start(&Analog1);

                // Sum all values the boring way
                *sumval = val[0] + val[1] + val[2] + val[3] + val[4] + val[5] + val[6] + val[7] + val[8] + val[9];
                *sumval = *sumval / 5;

                base = HAL_ADC_GetValue(&Analog2);
                HAL_ADC_Start(&Analog2);
                if (*sumval > base) {
                    // If we detect metal, act accordingly
                    *Metal_Found = 1;
                    Countdown_Start = 1;
                    Countdown_Time = HAL_GetTick(); // Find EndTime using HAL
                    // Turn on Buzzer
                    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
                } else {
                    if (Countdown_Start == 1) {
                        // If in count-down phase, check how much time has passed
                        // Currently 3 seconds -> 3000ms
                        if (HAL_GetTick() > 3000) {
                            // If count-down finished, turn off buzzer and say metal not detected
                            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
                            *Metal_Found = 0;
                            Countdown_Start = 0;
                        }
                    } else {
                        // Otherwise, make sure buzzer is off
                        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
                    }
                }
                *State = 1; // Always return to State 1
                break;
        }
        break;
    }
}
