/*
 * MainProject.c
 *
 *  Created on: 20 Sep 2024
 *      Author: ${Ahmed Saeed}
 */

// General use libraries
#include "STD_Types.h"
#include "BIT_Math.h"
#include "ctype.h"
#include "SystemFunctions.h"
#include "Login.h"
#include "Animation_Functions_LCD.h"
#include <util/delay.h>

// MCAL
#include "DIO.h"
#include "USART.h"
#include "ADC.h"
#include "TIM0.h"
#include "TIM1.h"

// HAL
#include "LCD.h"
#include "Buzzer.h"
#include "MOTORS.h"

uint8 u8DoorStateFlag = 0;
uint8 u8LightStateFlag = 0;
uint8 u8FanStateFlag = 0;

int main (void)
{
	// Used variables
	char acharUserEnterdNameLoc[7] = "dummy";
	char acharUserEnterdPasswordLoc[6] = "admn";
	uint8 u8UserExistenceCheckLoc, u8UserPositionLoc, u8PasswordTrialsLoc = 0, u8PasswordCheckLoc, u8AlarmCntrLoc = 0, u8UserChoice = 1;

	// System Initialization Sequence
	SystemInitialization();

	// ==========================================Mobile Interfacing Start====================================================

	// Delaying to start communication by receiving void
	// USART_u16RecvDataSync();
	USART_vidSendStringSynch("\nHello,");

	while (1)
	{
		LCD_vidWelcomeJiggle(0);
		LCD_vidLoadingAnimation(0, "Loading");

		// The following 4 lines could be in one function
		USART_vidSendStringSynch("\nEnter User Name: ");
		UserInputReceive(acharUserEnterdNameLoc, 6);

		//===========================================================
		// For assurance #will be deleted#
		LCD_vidSendCmd(0, LCD_CLR);
		LCD_vidWriteString(0, acharUserEnterdNameLoc);
		//===========================================================

		// Check UserName Existence
		u8UserExistenceCheckLoc = UserExistance(acharUserEnterdNameLoc, &u8UserPositionLoc);

		if (u8UserExistenceCheckLoc == Exist)
		{
			DIO_enuWritePin(9, 1); // Green LED to check it's right #will be deleted#
			_delay_ms(700);
			DIO_enuWritePin(9, 0); // Green LED to check it's right #will be deleted#

			// Receiving the Password
			USART_vidSendStringSynch("Enter Password: ");

			UserInputReceive(acharUserEnterdPasswordLoc, 4);

			u8PasswordCheckLoc = PasswordCheck(acharUserEnterdPasswordLoc, u8UserPositionLoc);

			LCD_vidSendCmd(0, LCD_CLR);

			while ((u8PasswordTrialsLoc != 2) && (u8PasswordCheckLoc != Exist))
			{
				u8PasswordTrialsLoc++; // Incremented here because the user has tried once

				USART_vidSendStringSynch("Wrong Password, Try again: ");
				UserInputReceive(acharUserEnterdPasswordLoc, 4);

				LCD_vidSendCmd(0, LCD_CLR);
				LCD_vidWriteString(0, acharUserEnterdPasswordLoc);

				u8PasswordCheckLoc = PasswordCheck(acharUserEnterdPasswordLoc, u8UserPositionLoc);
				_delay_ms(500);

				LCD_vidSendCmd(0, LCD_CLR);
			}

			// Check if the password is entered 3 times
			// This could also be handled using a flag set in the while loop when it reaches 3 times
			if (u8PasswordTrialsLoc == 2)
			{

				// Check if door is opened before triggering alarm
				if (u8DoorStateFlag == 1)
				{
					// Door is already opened without correct password
					TriggerEmergencyShutdown();
				}
				else
				{
					// Buzzer Alarm and Red LED
					while (u8AlarmCntrLoc != 10) // Just a number to loop the alarm system for a while
					{
						DIO_enuWritePin(9, 0);

						// Blink Red LED
						DIO_enuWritePin(8, 1);
						_delay_ms(300);
						DIO_enuWritePin(8, 0);

						// Alarm BUZZER
						startBuzzer();
						_delay_ms(500);
						stopBuzzer();
						_delay_ms(200);

						u8AlarmCntrLoc++;

						// Clear password trials anyway to make the retrying option valid
						u8PasswordTrialsLoc = 0;
					}
				}

			}
			else
			{
				/*======================= Authentication success ===================*/
				// System Starts
				WelcomeMsgDisplay();

				LCD_vidWriteString(0, "Welcome ");
				LCD_vidWriteString(0, acharUserEnterdNameLoc);

				u8UserChoice = 1;

				while (u8UserChoice != 0)
				{
					/*============== System Supported Features =========================*/
					// System Feature Menu
					SystemFeaturesMenuDisplay();


					// For feature improvements (Under Development);
//					uint8 u8TempLoc = ADC_u16ReadSync(ADC_CH3);
//					LCD_vidWriteNumber(0, u8TempLoc);


					// Receiving the user choice
					u8UserChoice = USART_u16RecvDataSync();

					// Polling sequence until getting valid data
					while (u8UserChoice < '0')
					{
						u8UserChoice = USART_u16RecvDataSync();
					}

					// Handle the case if the user enters lowercase character
					u8UserChoice = toupper(u8UserChoice);

					if (u8UserChoice > '0') // To make sure that only valid data goes to switch case
					{
						// ALL of these switch cases could be functions
						switch (u8UserChoice)
						{
						// Turn on Fan
						case 'A':
						{
							if (u8FanStateFlag == 1)
							{
								USART_vidSendStringSynch("Fan is already turned on sir :).\n");
							}
							else
							{
								u8FanStateFlag = 1;
								FanControl();
							}
							break;
						}

						// Turn off Fan
						case 'B':
						{
							if(u8FanStateFlag == 0)
							{
								USART_vidSendStringSynch("Fan is already turned off sir :).\n");
							}
							else
							{
								u8FanStateFlag = 0;

								FanStop();
								USART_vidSendStringSynch("Fan turned off\n");
							}

							break;
						}

						// Change Fan Speed
						case 'G':
						{
							ChangeFanSpeed(&u8FanStateFlag);
							break;
						}

						// Open the door using SERVO
						case 'D':
						{
							if (u8DoorStateFlag == 1)
							{
								USART_vidSendStringSynch("Door is already opened sir :).\n");
							}
							else
							{
								u8DoorStateFlag = 1;
								Servo_MotorRotate_0_TO_90();
							}

							break;
						}

						// Close the door using SERVO
						case 'C':
						{
							if (u8DoorStateFlag == 0)
							{
								USART_vidSendStringSynch("Door is already closed sir :).\n");
							}
							else
							{
								u8DoorStateFlag = 0;
								Servo_MotorRotate_90_To_0();

							}

							break;
						}

						/* Lights ON Case */
						case 'N':
						{
							HandleDevice(&u8LightStateFlag, 'N', "The lights are already on sir :)\n", "The lights are already off sir :)\n", LED_ON, LED_OFF, 15);
							break;
						}

						// Lights OFF
						case 'F':
						{
							HandleDevice(&u8LightStateFlag, 'F', "The lights are already on sir :)\n", "The lights are already off sir :)\n", LED_ON, LED_OFF, 15);
							break;
						}

						// System Logout
						case 'E':
						{
							USART_vidSendStringSynch(" \n Logging out..\n ");

							// >>>> Should do a shutdown sequence closing everything <<<<
							ShutDownSequence(&u8LightStateFlag, &u8DoorStateFlag, &u8FanStateFlag);
							_delay_ms(700);
							u8UserChoice = 0;
							break;
						}

						default:

							USART_vidSendStringSynch(" \n Please enter a valid option! \n ");
							break;
						}
					}
				}
			}
		}
		else
		{
			// User is not found in the system
			USART_vidSendStringSynch(" User Not Found\n");
			DIO_enuWritePin(8, 1);

			_delay_ms(700);
			DIO_enuWritePin(8, 0);

			// Should go back to enter user or exit the system
		}
	} // End of SuperLoop

	return 0;
}

