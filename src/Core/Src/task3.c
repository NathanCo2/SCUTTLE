/**
 * @file task3.c
 *
 * @brief Implementation of Task 3: OPENMV Camera Interface
 *
 * NOTE: THIS CODE IS INCLUDED FOR COMPLETENESS, BUT IS NOT USED IN THE IMPLEMENTATION OF THIS PROJECT
 * This file contains the implementation of the state machine for interfacing with the
 * OPENMV camera. It includes functions to request, receive, and process distance and angle
 * data from the camera via UART.
 *
 * @date Jun 5, 2024
 * @author tawel
 */

#include "task3.h"
#include <stdlib.h>

// Initialize in-task variables

int32_t Distance_Int; /**< Distance received from OPENMV */
int32_t Angle_Int; /**< Angle received from OPENMV */

uint8_t Req = 0; /**< Flag indicating if SPI request is pending */
uint8_t Dummy; /**< Dummy value used for debugging */

uint8_t Buffer[9]; /**< Buffer to store data received via UART */

// Task 3 state machine: OPENMV Camera
void task3_run(uint8_t* State, float* Distance_Target, float* Angle_Target, uint8_t* SPI_Rec,
               uint8_t* Follow, uint8_t* OpenMV, UART_HandleTypeDef UART3) {
    while (1) {
        switch (*State) {

            case 0:
                // State 0: INIT

                *State = 1;
                break;

            case 1:
                // State 1: Flag Check

                // If we are in follow mode and OpenMV mode, then
                if ((*Follow == 1) && (*OpenMV == 1)) {
                    if (*SPI_Rec == 0) {
                        if (Req == 0) {
                            // If we have not requested data yet, request
                            *State = 2; // Next State: Receive Data
                        } else {
                            *State = 1; // Otherwise stay in this state
                        }

                    } else {
                        *State = 3; // If we already received data, process it
                    }
                } else {
                    *State = 1;
                }

                break;

            case 2:
                // State 2: Receive Data

                HAL_UART_Receive(&UART3, Buffer, 9, 1000);

                Req = 1;

                *SPI_Rec = 1;

                *State = 1; // Go back to flag check and wait for receive

                break;

            case 3:
                // State 3: Process Data
                // Convert buffer data to ints. First part of buffer should be distance, second part angle
                Dummy = Buffer[0];
                if (Dummy == 85) {
                    // If we received usable data, then update setpoints
                    Distance_Int = (int32_t)(Buffer[1] << 24 | Buffer[2] << 16 | Buffer[3] << 8 | Buffer[4]);
                    Angle_Int = (int32_t)(Buffer[5] << 24 | Buffer[6] << 16 | Buffer[7] << 8 | Buffer[8]);

                    // Convert to float (assuming the data was sent as 32-bit floats)
                    *Distance_Target = (float)Distance_Int;
                    *Angle_Target = (float)Angle_Int;
                }

                // Once data is fully processed, return to state 1 and reset receive flag
                *SPI_Rec = 0;
                *State = 1;
                Req = 0; // Reset Request

                break;

        }

        break;
    }

}