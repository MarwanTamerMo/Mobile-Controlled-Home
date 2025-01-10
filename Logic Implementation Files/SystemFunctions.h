/*
 * SystemFunctions.h
 *
 * Created on: 23 Sep 2024
 * Author: Ahmed Saeed
 */

/*********************************************************************/
/* Description: Interface file for various system control functions  */
/* Version: 1.0 V                                                    */
/*********************************************************************/

#ifndef SYSTEMFUNCTIONS_H_
#define SYSTEMFUNCTIONS_H_

#include "STD_Types.h"

/*
 * Function to display the system features menu
 */
void SystemFeaturesMenuDisplay(void);

/*
 * Function to display a welcome message
 */
void WelcomeMsgDisplay(void);

/*
 * Function to turn on a specified LED
 * Parameters:
 *   LEDPinCpy (uint8): Pin number of the LED
 */
void LED_ON(uint8 LEDPinCpy);

/*
 * Function to turn off a specified LED
 * Parameters:
 *   LEDPinCpy (uint8): Pin number of the LED
 */
void LED_OFF(uint8 LEDPinCpy);

/*
 * Function to control fan speed
 */
void FanControl(void);

/*
 * Function to stop the fan
 */
void FanStop(void);

/*
 * Function to change the speed of the fan
 * Parameters:
 *   pu8FanState (uint8*): Pointer to fan state (speed)
 */
void ChangeFanSpeed(uint8* pu8FanState);

/*
 * Function to handle a device's state (turn on/off)
 * Parameters:
 *   u8state (uint8*): Pointer to device state
 *   command (uint8): Command to be executed
 *   onMsg (char*): Message to display when turning on
 *   offMsg (char*): Message to display when turning off
 *   TurnOnFunc (void (*)(uint8)): Function pointer for turning on
 *   TurnOffFunc (void (*)(uint8)): Function pointer for turning off
 *   u8PinNumCpy (uint8): Pin number for the device
 */
void HandleDevice(uint8 *u8state, uint8 command, char* onMsg, char* offMsg, vidPfu8 TurnOnFunc, vidPfu8 TurnOffFunc, uint8 u8PinNumCpy);

/*
 * Function to trigger emergency system shutdown
 */
void TriggerEmergencyShutdown(void);

/*
 * Function to initialize the system
 */
void SystemInitialization(void);

/*
 * Function to handle system shutdown sequence
 * Parameters:
 *   u8LightStateFlag (uint8*): Pointer to light state flag
 *   u8DoorStateFlag (uint8*): Pointer to door state flag
 *   u8FanStateFlag (uint8*): Pointer to fan state flag
 */
void ShutDownSequence(uint8 *u8LightStateFlag, uint8 *u8DoorStateFlag, uint8 *u8FanStateFlag);

/*
 * Function to handle ADC ISR action (Under Development)
 * Parameters:
 *   u16DigDataLoc (uint16): Digital data from ADC
 */
void ISR_ADC_Action(uint16 u16DigDataLoc); // For future improvements (Under Development)

#endif /* SYSTEMFUNCTIONS_H_ */
