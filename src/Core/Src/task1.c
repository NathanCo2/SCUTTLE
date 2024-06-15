/*
 * task1.c
 *
 *  Created on: Jun 3, 2024
 *      Author: tawel
 */

#include "task1.h"

/**
 * @file task1.c
 * @brief Task 1: Diagnostics Test
 *
 * Runs a diagnostic test, including battery level check to ensure battery does not get to dangerous level.
 * @date June 3, 2024
 * @author tawel
 */

/** Battery reading, should not be below 3303 */
uint16_t Bat_Res = 0;

/**
 * @brief Run task 1 FSM, which includes diagnostics and battery level check.
 * @param State Pointer to the state variable.
 * @param Analog2 ADC handle for battery level check.
 * @param Kill Pointer to the kill switch variable.
 */
void task1_run(uint8_t* State, ADC_HandleTypeDef Analog2,uint8_t* Kill) {
    // Task 1 implementation
    while(1) {
        switch(*State) {

        case 0:
            // State 0: INIT
            // Initialize ADC
            HAL_ADC_Start(&Analog2);
            // Analog2.Init.EOCSelection = DISABLE; //Apparently important
            // Set Variables

            *State = 1;

            break;

        case 1:
            // State 1: Check Battery
            // Read ADC, make sure good for conversion first

            Bat_Res = HAL_ADC_GetValue(&Analog2);
            Bat_Res = HAL_ADC_GetValue(&Analog2); // Have to do it twice i think
            HAL_ADC_Start(&Analog2);

            if (Bat_Res < 3303) {
                // If battery too low, turn everything off, they should be on by default
                *Kill = 1; // Kill if battery too low
            }

            *State = 1; // Always return to state 1

            break;

        }
        break;
    }
}
