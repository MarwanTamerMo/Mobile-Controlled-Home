/*
 * MOTORS.c

 *
 *  Created on: 24 Jul 2024
 *      Author: ${Ahmed Saeed}
 */
#include "STD_Types.h"

#include "DIO.h"

#include "MOTORS.h"

#include "TIM1_priv.h"
#include "TIM1.h"
#include "TIM2.h"

#include <util/delay.h>

void DC_MotorSetSpeed(uint8 u8SpeedCpy)
{
	// Set the direction to rotate (CW/CCW can be added as needed)
//	    DIO_enuWritePin(u8LeftPinCpy, 0);
//	    DIO_enuWritePin(u8RightPinCpy, 1);

	    // Set PWM based on the required speed
	    switch(u8SpeedCpy)
	    {
	    	case 0: // Turn off motor
//	    		DIO_enuWritePin(u8LeftPinCpy, 0);
//	    		DIO_enuWritePin(u8RightPinCpy, 0);
	    		TIM2_vidDisconnectOC2();
	    		break;

	        case 1: // 25% duty cycle
	        	TIM2_vidConnectOC2(); // Enable OC2 pin to generate PWM
	            TIM2_vidSetValueOcr(64); // Assuming 255 as full count, 64 is ~25% of 255
	            break;

	        case 2: // 50% duty cycle
	        	TIM2_vidConnectOC2(); // Enable OC2 pin to generate PWM
	            TIM2_vidSetValueOcr(128); // 50% of 255
	            break;

	        case 3: // 100% duty cycle
	        	TIM2_vidConnectOC2(); // Enable OC2 pin to generate PWM
	            TIM2_vidSetValueOcr(255); // Full speed
	            break;

	        default: // Stop motor if invalid speed is passed
	        	TIM2_vidDisconnectOC2();
	            break;
	    }
}

void DC_MotorRotateCW(uint8 u8LeftPinCpy, uint8 u8RightPinCpy)
{
	//rotates right to left
	DIO_enuWritePin(u8LeftPinCpy,0);
	DIO_enuWritePin(u8RightPinCpy,1);
}
void DC_MotorRotateCCW(uint8 u8LeftPinCpy, uint8 u8RightPinCpy)
{
	//rotates left to right
	DIO_enuWritePin(u8RightPinCpy,0);
	DIO_enuWritePin(u8LeftPinCpy,1);
}
void DC_MotorBreak(uint8 u8LeftPinCpy, uint8 u8RightPinCpy)
{
	//Break motor
	DIO_enuWritePin(u8LeftPinCpy,0);
	DIO_enuWritePin(u8RightPinCpy,0);
}


void Servo_MotorRotate(uint8 u8DegreeCpy)
{
	/*Firstly make ICR=19999 Const.*/
	TIM1_vidSetValueIcr(19999);
	/*Based on the degree assign the corresponding value of OCR1A*/

	switch (u8DegreeCpy)
	{
	case 0:
		TIM1_vidSetValueOcr_A(550);
		break;
	case 90:
		TIM1_vidSetValueOcr_A(1600);
		break;
	case 180:
		TIM1_vidSetValueOcr_A(2450);
		break;
	}
}

void Servo_MotorRotate_0_TO_180(void)
{
	uint16 i;

	for (i = 550; i < 2500; i++)
	{
		TIM1_vidSetValueOcr_A(i);
		_delay_ms(2);
	}
}

void Servo_MotorRotate_180_To_0(void)
{
	uint16 i;

	for (i = 2500; i > 550; i--)
	{
		TIM1_vidSetValueOcr_A(i);
		_delay_ms(2);
	}
}

void Servo_MotorRotate_90_To_0(void)
{
	uint16 i;

	for (i = 1600; i > 550; i--)
	{
		TIM1_vidSetValueOcr_A(i);
		_delay_ms(2);
	}
}


void Servo_MotorRotate_0_TO_90(void)
{
	uint16 i;

	for (i = 550; i < 1600; i++)
	{
		TIM1_vidSetValueOcr_A(i);
		_delay_ms(2);
	}
}
