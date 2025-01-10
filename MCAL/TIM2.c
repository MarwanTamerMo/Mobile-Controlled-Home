#include "STD_Types.h"
#include "BIT_Math.h"

#include "TIM2.h"
#include "TIM2_cfg.h"
#include "TIM2_priv.h"


pf TIM2_CallBack_Ovf = stub ;
pf TIM2_CallBack_Cmp = stub ;

void TIM2_vidInit(void)
{
  uint8 u8Tccr2_pre = 0 ;
  
  #if   TIM2_MODE == TIM2_NORMAL
	CLR_BIT(u8Tccr2_pre , 6);
	CLR_BIT(u8Tccr2_pre , 3);
	
  #elif TIM2_MODE == TIM2_PHASE_CORR
	SET_BIT(u8Tccr2_pre , 6);
	CLR_BIT(u8Tccr2_pre , 3);
	
  #elif TIM2_MODE == TIM2_CTC
	CLR_BIT(u8Tccr2_pre , 6);
	SET_BIT(u8Tccr2_pre , 3);
	
  #elif TIM2_MODE == TIM2_FAST_PWM
	SET_BIT(u8Tccr2_pre , 6);
	SET_BIT(u8Tccr2_pre , 3);
  
  #endif 
  
	u8Tccr2_pre = u8Tccr2_pre | TIM2_CLK_SEL;
	u8Tccr2_pre = u8Tccr2_pre | TIM2_COM_BITS<<4;
	TCCR2 = u8Tccr2_pre;
	
}

void TIM2_vidEnableOvfIreq(void)
{
	SET_BIT(TIMSK,6);
}
void TIM2_vidDisableOvfIreq(void)
{
	CLR_BIT(TIMSK,6);	
}

void TIM2_vidEnableCmpIreq(void)
{
	SET_BIT(TIMSK,7);
}
void TIM2_vidDisableCmpIreq(void)
{
	CLR_BIT(TIMSK,7);
}

void TIM2_vidSetCallbackOvf(pf pfCallBackCpy)
{
	TIM2_CallBack_Ovf = pfCallBackCpy ;
}
void TIM2_vidSetCallbackCmp(pf pfCallBackCpy)
{
	TIM2_CallBack_Cmp = pfCallBackCpy ;
}

void TIM2_vidSetValueTcnt(uint8 u8ValueCpy)
{
	TCNT2 = u8ValueCpy ;
}
void TIM2_vidSetValueOcr(uint8 u8ValueCpy)
{
	OCR2 = u8ValueCpy ;
}

uint8 TIM2_u8GetValueTcnt(void)
{
	return TCNT2 ;
}

void TIM2_vidDisconnectOC2(void)
{
	// Clear COM00 and COM01 to disconnect OC2
	CLR_BIT(TCCR2, 4); // COM20 Bit
	CLR_BIT(TCCR2, 5); // COM21 Bit
}

void TIM2_vidConnectOC2(void)
{
	// Set COM01 and clear COM00 to connect OC2 (non-inverting mode)
	CLR_BIT(TCCR2, 4); // COM20 Bit
	SET_BIT(TCCR2, 5); // COM21 Bit
}

/*Compare match ISR*/
void __vector_4 (void) __attribute__((signal, used));
void __vector_4 (void)
{
	TIM2_CallBack_Cmp();
}

/*Overflow ISR*/
void __vector_5 (void) __attribute__((signal, used));
void __vector_5 (void)
{
	TIM2_CallBack_Ovf();
}

static void stub(void)
{
	
} 
