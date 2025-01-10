/*
 * SystemFunctions.c
 *
 *  Created on: 23 Sep 2024
 *      Author: ${Ahmed Saeed}
 */

// Header file
#include "SystemFunctions.h"

// General use libraries
#include "STD_Types.h"
#include "BIT_Math.h"
#include "Animation_Functions_LCD.h"
#include "Login.h"
#include <util/delay.h>

// MCAL
#include "DIO.h"
#include "USART.h"
#include "TIM0.h"
#include "TIM1.h"
#include "TIM2.h"
#include "ADC.h"
#include "GIE.h"

// HAL
#include "MOTORS.h"
#include "Buzzer.h"
#include "LCD.h"

void SystemInitialization(void)
{
	/* Initialization Sequence */
	    // DIO (GPIO) Initialization
	    DIO_vidInit();

	    // ADC Initialization and Enable
	    ADC_vidInit();
	    ADC_vidEnable();

	    // USART Initialization
	    USART_vidInit();

	    // LCD Initialization
	    LCD_vidInit();

	    // Timers (0-2) Initializations
	    TIM1_vidInit();
	    TIM0_vidInit();
	    TIM2_vidInit();

	    // Make sure to stop the fan in the start of the system
	    FanStop();

	    // Setting buzzer frequency and make sure it's not operational it at the start
	    setBuzzerFrequency(2000);
	    stopBuzzer();

	    // Set ICR Value to control the servo motor (Door)
	    TIM1_vidSetValueIcr(19999);

	    // Now enable ADC interrupts after other initializations are done (Under development)
	    ADC_vidEnableIntReq();

	    // GIE (General Interrupt control register) Enable
	    GIE_vidEnable();

}

void SystemFeaturesMenuDisplay (void)
{
	USART_vidSendStringSynch(" \nInput Your Order Character: \n");
	USART_vidSendStringSynch(" A: Turn On Fan \n");
	USART_vidSendStringSynch(" B: Turn Off Fan \n");
	USART_vidSendStringSynch(" G: Change Fan Speed \n");
	USART_vidSendStringSynch(" D: Open Door \n");
	USART_vidSendStringSynch(" C: Close Door \n");
	USART_vidSendStringSynch(" N: Lights ON \n");
	USART_vidSendStringSynch(" F: Lights OFF \n");
	USART_vidSendStringSynch(" E: System Logout \n");

}

void WelcomeMsgDisplay(void)
{
	USART_vidSendStringSynch("\n ******************\n ");
	USART_vidSendStringSynch("  Welcome Back :) \n ");
	USART_vidSendStringSynch(" ******************\n ");
}


void FanControl(void)
{
	uint8 u8FanSpeedLoc = 0;

	USART_vidSendStringSynch("\n Please Choose the speed of the fan you want, sir :) \n");

	USART_vidSendStringSynch(" 1- Lowest \n");
	USART_vidSendStringSynch(" 2- Medium \n");
	USART_vidSendStringSynch(" 3- Max \n");

	// Receive user choice for speed
	while((u8FanSpeedLoc !='1')&&(u8FanSpeedLoc !='2')&&(u8FanSpeedLoc !='3'))
	{
	u8FanSpeedLoc = (char)USART_u16RecvDataSync();
	_delay_ms(50);
	}

	// Set motor speed based on user's choice
	switch ((char)u8FanSpeedLoc)
	{
		case '1':
			DC_MotorSetSpeed(1);  // Set to 25% speed (Low)
			USART_vidSendStringSynch("Fan speed set to LOW\n");
			break;

		case '2':
			DC_MotorSetSpeed(2);  // Set to 50% speed (Medium)
			USART_vidSendStringSynch("Fan speed set to MEDIUM\n");
			break;

		case '3':
			DC_MotorSetSpeed(3); // Set to 100% speed (Max)
			USART_vidSendStringSynch("Fan speed set to MAX\n");
			break;

		default:
			USART_vidSendStringSynch("Invalid choice. Try again.\n");
			break;
	}

}

void FanStop(void)
{
	TIM2_vidDisconnectOC2();
}

void ChangeFanSpeed(uint8* u8FanState)
{
	uint8 u8ChoiceLoc;

	if(*u8FanState == 1)
	{
		FanControl();
	}
	else
	{
		USART_vidSendStringSynch("The Fan is turned off sir do you want to turn it on? (y/n): ");
		u8ChoiceLoc = USART_u16RecvDataSync();

		if(u8ChoiceLoc == 'y')
		{
			*u8FanState = 1;
			FanControl();
		}
		else
		{
			/* Do Nothing */
		}

	}
}

void LED_ON(uint8 LEDPinCpy)
{
	DIO_enuWritePin(LEDPinCpy, 1);
}
void LED_OFF(uint8 LEDPinCpy)
{
	DIO_enuWritePin(LEDPinCpy, 0);
}

void ShutDownSequence(uint8 *u8LightStateFlag, uint8 *u8DoorStateFlag, uint8 *u8FanStateFlag)
{
    // Send shutdown message
    USART_vidSendStringSynch("System is shutting down...\n");
    LCD_vidLoadingAnimation(0,"Shutting down");

    // Turn off the lights if they are on
    if (*u8LightStateFlag == 1)
    {
        LED_OFF(15); // Assuming pin 15 controls the lights
        *u8LightStateFlag = 0;
        USART_vidSendStringSynch("Lights turned off.\n");
    }

    // Close the door if it's open
    if (*u8DoorStateFlag == 1)
    {
    	Servo_MotorRotate_90_To_0(); // Close the door
        *u8DoorStateFlag = 0;
        USART_vidSendStringSynch("Door closed.\n");
    }

    // Turn off the fan if it's turned on
	if (*u8FanStateFlag == 1)
	{
		FanStop(); // Turn off the fan
		*u8FanStateFlag = 0;
		USART_vidSendStringSynch("Fan turned off.\n");
	}

    // Deactivate buzzer (if operational)
    stopBuzzer();

    // Final message and halt the system
    USART_vidSendStringSynch("System shutdown complete. Goodbye!\n");
    LCD_vidWriteString(0, "Goodbye");

    // Optionally, halt the system indefinitely (still thinking about a more convenient way for this)
    _delay_ms(1500);
//  while (1); // This will prevent further operations
}


void HandleDevice(uint8 *u8state, uint8 command, char* onMsg, char* offMsg, vidPfu8 TurnOnFunc, vidPfu8 TurnOffFunc, uint8 u8PinNumCpy)
{
	 if (command == 'N') // ON command
	 {
	        if (*u8state == 1)
	        {
	            USART_vidSendStringSynch(onMsg); // Already ON message
	        }
	        else
	        {
	            *u8state = 1;
	            TurnOnFunc(u8PinNumCpy); // Turn on the device
	            USART_vidSendStringSynch("Lights are turned on :) \n");
	        }

	 }
	 else if (command == 'F') // OFF command
	 {
	        if (*u8state == 0)
	        {
	            USART_vidSendStringSynch(offMsg); // Already OFF message
	        }
	        else
	        {
	            *u8state = 0;
	            TurnOffFunc(u8PinNumCpy); // Turn off the device
	            USART_vidSendStringSynch("Lights are turned off :) \n");
	        }
	    }
}

void TriggerEmergencyShutdown(void)
{
    // Alarm on UART and LCD
    USART_vidSendStringSynch("Calling 911...\n");
    LCD_vidSendCmd(0, LCD_CLR);
    LCD_vidWriteString(0, "Calling 911");

    // Activate buzzer
    startBuzzer();

    // Shutdown sequence
    LED_OFF(15); // Turn off lights
    Servo_MotorRotate_90_To_0(); // Close the door
    FanStop(); // Turn off the fan


    // Stop the system
    // Infinite loop to halt the system
    while (1)
    {
    	startBuzzer();
    	_delay_ms(500);
    	stopBuzzer();
    	_delay_ms(500);
    }
}

// Under Development
void ISR_ADC_Action(uint16 u16DigDataLoc)
{

//	float32 u16AnalogMvDataLoc = 0;
//	uint16 u8TempLoc = 0;
//
//	// Convert digital value to millivolts and then to temperature
//	u16AnalogMvDataLoc = u16DigDataLoc * (5000.0 / 1024);
//	u8TempLoc = u16AnalogMvDataLoc / 10;
//
//	// Display the temperature value on the LCD
//	LCD_vidSendCmd(1, LCD_CLR);
//	LCD_vidSendCmd(1, LCD_FIRST_LINE);
//	LCD_vidWriteNumber(1, u8TempLoc);
//
//	// Introduce a small delay to avoid overwhelming the system
//	_delay_ms(500); // Give it some time before starting the next conversion
//
//	// Restart ADC conversion
//	ADC_vidStartConv();

}
