/*
 * task2.c
 *
 *  Created on: Jun 3, 2024
 *      Author: tawel
 */

#include "task2.h"
#include <stdlib.h>

/**
 * @file task2.c
 * @brief Task 2: Radio Killswitch
 *
 * Checks radio killswitch and battery killswitch and update run flags accordingly.
 * @date June 3, 2024
 * @author tawel
 */

/**
 * @brief Run task 2 FSM, which includes checking the radio killswitch and activating the metal detector.
 * @param State Pointer to the state variable.
 * @param BatKill Pointer to the battery kill switch flag.
 * @param RadKill Pointer to the radio kill switch flag.
 * @param usWidth Pointer to the pulse width flag.
 * @param DriveON Pointer to the drive system status flag.
 * @param ArmON Pointer to the arm system status flag.
 * @param MDON Pointer to the metal detector on/off flag.
 * @param OPENMV Pointer to the OpenMV camera status flag.
 */
void task2_run(uint8_t* State, uint8_t* BatKill, uint8_t* RadKill, int* usWidth, uint8_t* DriveON, uint8_t* ArmON, uint8_t* MDON, uint8_t* OPENMV)
{
    // Task 2 implementation
    while(1) {
        switch(*State) {

        case 0:
            // State 0: INIT
            *State = 1;
            break;

        case 1:
            // State 1: Check Battery
            // Check Radio First, then Battery
            // Supposed to be 1500, max plus minus 400
            if((abs(*usWidth - 1950) > 200) & (*usWidth > 500)) {
                *RadKill = 1;
                // Kill all motors and metal detector
                *DriveON = 0;
                *ArmON = 0;
                *MDON = 0;
            } else {
                *RadKill = 0;
                // Turn on Metal Detector, motors
                *DriveON = 1;
                *ArmON = 1;
                *MDON = 1;
            }

            if (*BatKill == 1) {
                // Kill Everything
                *DriveON = 0;
                *ArmON = 0;
                *MDON = 0;
                *OPENMV = 0;
            }

            *State = 1; // Always return to state 1
            printf("%d\r\n", *usWidth);
            break;

        }
        break;
    }
}
