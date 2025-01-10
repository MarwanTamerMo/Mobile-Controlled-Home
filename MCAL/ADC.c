/*
 * ADC.c
 *
 *  Created on: May 14, 2024
 *      Author: Marwan
 */


#include "STD_Types.h"
#include "BIT_Math.h"

#include "ADC.h"
#include "ADC_cnfg.h"
#include "ADC_priv.h"
#include "LCD.h"


static volatile vidPfu16 ADC_PfCallback = ADC_Stub ;

uint8 ADC_u8ChSelected = 0 ;

void ADC_vidInit(void)
{

	uint8 u8ADMUX_Pre  = 0;
	uint8 u8ADCSRA_Pre = 0;

	u8ADMUX_Pre = (ADC_VREF<<6)|(ADC_ADJ_MODE<<5)|ADC_CH_SEL ;

	u8ADCSRA_Pre = (ADC_TRIGGER_MODE<<5)|ADC_PRESCALLER ;

#if   ADC_TRIGGER_MODE == ADC_AUTO_TRIGGER
			SFIOR &= 0x1F; /*CLR 3 msbs*/
			SFIOR |= ADC_AUTO_TRIGGER_SRC << 5;
#endif

	ADMUX  = u8ADMUX_Pre;
	ADCSRA = u8ADCSRA_Pre;

	ADC_u8ChSelected = ADC_CH_SEL ;
/*
NOTE :
ADC OFF
ADC IREQ OFF
*/

}

void ADC_vidEnable(void)
{
	SET_BIT(ADCSRA,7);
}
void ADC_vidDisable(void)
{
	CLEAR_BIT(ADCSRA,7);
}

void ADC_vidEnableIntReq(void)
{
	SET_BIT(ADCSRA , 3);
}
void ADC_vidDisableIntReq(void)
{
	CLEAR_BIT(ADCSRA , 3);
}

void ADC_vidSelCh(uint8 u8ChNoCpy)
{
	if (u8ChNoCpy <= 31)
	{
		ADMUX = ADMUX & 0b11100000;
		ADMUX = ADMUX | u8ChNoCpy ;
		ADC_u8ChSelected = u8ChNoCpy ;
	}
	else
	{
		/*Do Nothing*/
	}
}
void ADC_vidStartConv(void)
{
	SET_BIT(ADCSRA , 6 );
}

uint16  ADC_u16ReadSync(uint8 u8ChNoCpy)
{
	uint16 u16DataLoc = 0 ;
	/*select channel*/
	  ADC_u8ChSelected = u8ChNoCpy ;
	  ADC_vidSelCh(u8ChNoCpy);

	/*start conv*/
	  ADC_vidStartConv();
	/*wait conv complete*/
	while (GET_BIT(ADCSRA , 4) !=1);
	LCD_vidWriteNumber(0, 1);

	/*read data left (H), Right (L,H)*/
	#if  ADC_ADJ_MODE  == ADC_RIGHT_ADJ

		u16DataLoc  = (uint16)ADCL ;
		u16DataLoc |= (uint16)((uint16)ADCH <<8) ;


		LCD_vidWriteNumber(0, 2);
	#else
	u16DataLoc = (uint16)ADCH ;
    #endif
	/*Diffrential*/
	if (u8ChNoCpy>=8 && u8ChNoCpy<=29)
	{
		/*read data left (H), Right (L,H)*/
	 	#if  ADC_ADJ_MODE  == ADC_RIGHT_ADJ
			if (GET_BIT(u16DataLoc,9) == 1 )
			{
				/*Negtive*/

				u16DataLoc = (~u16DataLoc)+1;
				u16DataLoc = u16DataLoc & 0x03FF;


			}
		#else
			if (GET_BIT(u16DataLoc,7) == 1 )
			{
				/*Negtive*/
				u16DataLoc = (~u16DataLoc)+1 ;
				u16DataLoc = u16DataLoc &0x00FF ;

			}
		#endif
	}

	/*clr flag */
	 SET_BIT(ADCSRA,4);

	 LCD_vidWriteNumber(0, 3);
	/*return Data*/
	return u16DataLoc ;


}

void ADC_vidSetCallBack(vidPfu16 pfCallBackCpy)
{
	ADC_PfCallback = pfCallBackCpy ;
}

void __vector_16 (void) __attribute__((signal,used));
void __vector_16 (void)
{
	volatile uint16 u16DataLoc = 0 ;
	/*read data left (H), Right (L,H)*/
	#if  ADC_ADJ_MODE  == ADC_RIGHT_ADJ
		u16DataLoc  = (uint16)ADCL ;
		u16DataLoc |= (uint16)((uint16)ADCH <<8) ;

	#else
		u16DataLoc = (uint16)ADCH ;
    #endif
	/*Diffrential*/
	if (ADC_u8ChSelected>=8 && ADC_u8ChSelected<=29)
	{
		/*read data left (H), Right (L,H)*/
		#if  ADC_ADJ_MODE  == ADC_RIGHT_ADJ
		if (GET_BIT(u16DataLoc,9) == 1 )
		{
			/*Negtive*/

			u16DataLoc = (~u16DataLoc)+1;
            u16DataLoc = u16DataLoc & 0x03FF;


		}
		#else
		if (GET_BIT(u16DataLoc,7) == 1 )
		{
			/*Negtive*/
			u16DataLoc = (~u16DataLoc)+1 ;
			u16DataLoc = u16DataLoc &0x00FF ;

		}
		#endif
	}


	ADC_PfCallback(u16DataLoc);
}


static void ADC_Stub (uint16 x)
{


}
