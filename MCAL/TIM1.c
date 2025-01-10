#include "STD_Types.h"
#include "BIT_Math.h"

#include "TIM1.h"
#include "TIM1_cfg.h"
#include "TIM1_priv.h"


static void stub()
{

}

pf TIM1_CallBack_Ovf = stub;
pf TIM1_CallBack_Cmp_CHA = stub;
pf TIM1_CallBack_Cmp_CHB = stub;
pf TIM1_CallBack_ICR = stub;

void TIM1_vidInit(void)
{
/*Instead of multiple #ifs, it can be done using preparation of the value that will be put into the
 * registers TCCR1A and TCCR1B*/
	//1. creating 2 preparation variables
	uint8 u8TCCR1A_prep = 0, u8TCCR1B_prep = 0; // 0b0000 0000

	//for ex: TCCR1A should be =0b COM1A1 COM1A0 COM1B1 COM1B0 FOC1A FOC1B WGM11 WGM10;

	u8TCCR1A_prep = (TIM1_COM_BITS_CHA <<6) | (TIM1_COM_BITS_CHB<<4) | (TIM1_MODE &0b00000011);
	//TCCR1B should be =0b ICNC1 ICES1 - WGM13 WGM12 CS12 CS11 CS10;
	u8TCCR1B_prep = (TIM1_NC <<7) | (TIM1_EDG_SLCT<<6)| ((TIM1_MODE>>2)<<3)  | (TIM1_CLK_SEL);




	// 3.put the prepared values of registers into the actual registers
	TCCR1A = u8TCCR1A_prep;
	TCCR1B = u8TCCR1B_prep;

}

/*OverFlow INT*/
void TIM1_vidEnableOvfIreq(void)
{
	SET_BIT(TIMSK,2);
}
void TIM1_vidDisableOvfIreq(void)
{
	CLR_BIT(TIMSK,2);
}

/*Compare match for Channel B*/
void TIM1_vidEnableCmp_BIreq(void)
{
	SET_BIT(TIMSK,3);

}

void TIM1_vidDisableCmp_BIreq(void)
{
	CLR_BIT(TIMSK,3);
}

/*Compare match for Channel A*/
void TIM1_vidEnableCmp_AIreq(void)
{
	SET_BIT(TIMSK,4);

}

void TIM1_vidDisableCmp_AIreq(void)
{
	CLR_BIT(TIMSK,4);
}

/*Input Capture INT */
void TIM1_vidEnableICUIreq(void)
{
	SET_BIT(TIMSK,5);

}

void TIM1_vidDisableICUIreq(void)
{
	CLR_BIT(TIMSK,5);
}


void TIM1_vidSetCallbackOvf(pf pfCallBackCpy)
{
	TIM1_CallBack_Ovf = pfCallBackCpy ;
}
void TIM1_vidSetCallbackCmp_CHA(pf pfCallBackCpy)
{
	TIM1_CallBack_Cmp_CHA = pfCallBackCpy ;
}
void TIM1_vidSetCallbackCmp_CHB(pf pfCallBackCpy)
{
	TIM1_CallBack_Cmp_CHB = pfCallBackCpy ;
}
void TIM1_vidSetCallbackICU(pf pfCallBackCpy)
{
	TIM1_CallBack_ICR = pfCallBackCpy ;
}
void TIM1_vidSetValueTcnt(uint16 u16ValueCpy)
{

	TCNT1H = (uint8)( u16ValueCpy>>8) ;
	TCNT1L = (uint8)u16ValueCpy;
}
void TIM1_vidSetValueOcr_A(uint16 u16ValueCpy)
{
	OCR1AH = (uint8 )(u16ValueCpy >> 8);
	OCR1AL = (uint8 ) u16ValueCpy;
}



void TIM1_vidSetValueOcr_B(uint16 u16ValueCpy)
{
	OCR1BH = (uint8) (u16ValueCpy >> 8);
	OCR1BL = (uint8) u16ValueCpy;
}

void TIM1_vidSetValueIcr(uint16 u16ValueCpy)
{
	ICR1H = (uint8) (u16ValueCpy >> 8);
	ICR1L = (uint8) u16ValueCpy;
}

uint16 TIM1_u16GetValueTcnt(void)
{
	return (uint16)TCNT1L |(uint16)TCNT1H<<8 ;
}

uint16 TIM1_u16GetValueICR(void)
{
	return (uint16)ICR1L |(uint16)ICR1H<<8 ;
}

void TIM1_vidChangeSenseICU(uint8 u8SenseCpy)
{
	if (u8SenseCpy==TIM1_EDGSELEC_FAL)
	{
		CLR_BIT(TCCR1B,6);
	}
	else if (u8SenseCpy==TIM1_EDGSELEC_RIS)
	{
		SET_BIT(TCCR1B,6);
	}
	else
	{
		/*Do nothing cuz wrong sense*/
	}
}


/*Compare match ISR*/
void __vector_6 (void) __attribute__((signal, used));
void __vector_6 (void)
{
	TIM1_CallBack_ICR();
}

/*Overflow ISR*/
void __vector_7 (void) __attribute__((signal, used));
void __vector_7 (void)
{
	TIM1_CallBack_Cmp_CHA();
}

void __vector_8 (void) __attribute__((signal, used));
void __vector_8 (void)
{
	TIM1_CallBack_Cmp_CHB();
}

void __vector_9 (void) __attribute__((signal, used));
void __vector_9 (void)
{
	TIM1_CallBack_Ovf();
}
