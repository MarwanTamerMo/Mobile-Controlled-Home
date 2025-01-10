/*
 * Buzzer.c
 *
 *  Created on: Sep 29, 2024
 *      Author: Marwan Tamer
 */
#include "Buzzer.h"
#include "TIM0.h"
#include "STD_Types.h"

#define F_CPU 8000000UL  // Define CPU frequency (8 MHz)

void startBuzzer(void)
{
	// Enable Timer 0 OC0 pin to start the PWM signal
	TIM0_vidConnectOC0();
}
void stopBuzzer(void)
{
	// Disable Timer 0 OC0 pin to stop the PWM signal
	TIM0_vidDisconnectOC0();
}
void setBuzzerFrequency(uint16 u16freq)
{
	/* Example:
	 *
	 * OC0 freq always constant with prescaler
	 *
	 * OC0 freq = 8 MHz / (255 * prescaler value [8])
	 *
	 * freq = 3922 Hz approx
	 *
	 * Total time = 1 / 3922 = 255us approx
	 *
	 * Duty cycle = (OCR [200] / 255)
	 *
	 * so Duty cycle = 78.5% approx
	 *
	 * Ton = 200us, Toff = 255us
	 *
	 * */

	uint16 u16OcrValue = (F_CPU / (2 * 8 * u16freq)) - 1;

	// Ensure OCR0 is within valid range (0-255)
	if (u16OcrValue > 255)
	{
		u16OcrValue = 255;
	}

	// Set the calculated OCR0 value
	TIM0_vidSetValueOcr((uint8) u16OcrValue);
}
