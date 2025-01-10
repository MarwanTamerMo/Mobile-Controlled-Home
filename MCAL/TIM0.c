#include "STD_Types.h"
#include "BIT_Math.h"

#include "TIM0.h"
#include "TIM0_cfg.h"
#include "TIM0_priv.h"


pf TIM0_CallBack_Ovf = stub;
pf TIM0_CallBack_Cmp = stub;
#define x CONC_(A1,TIM0_MODE)

#if x == 10
#undef TIM0_MODE
#define TIM0_MODE TIM0_NORMAL
#endif

void TIM0_vidInit(void)
{
  uint8 u8Tccr0_pre = 0 ;

  #if   TIM0_MODE == TIM0_NORMAL
  	  CLR_BIT(u8Tccr0_pre , 6);
  	  CLR_BIT(u8Tccr0_pre , 3);

  #elif TIM0_MODE == TIM0_PHASE_CORR
  	  SET_BIT(u8Tccr0_pre , 6);
  	  CLR_BIT(u8Tccr0_pre , 3);

  #elif TIM0_MODE == TIM0_CTC
  	  CLR_BIT(u8Tccr0_pre , 6);
  	  SET_BIT(u8Tccr0_pre , 3);

  #elif TIM0_MODE == TIM0_FAST_PWM
  	  SET_BIT(u8Tccr0_pre , 6);
  	  SET_BIT(u8Tccr0_pre , 3);

  #endif
  	  u8Tccr0_pre = u8Tccr0_pre | TIM0_CLK_SEL;
  	  u8Tccr0_pre = u8Tccr0_pre | TIM0_COM_BITS<<4;
  	  TCCR0 = u8Tccr0_pre ;

}

void TIM0_vidStart()
{
	// This function may also enable interrupts if needed
	 SET_BIT(TIMSK, 0); // Enable overflow interrupt if needed
	 SET_BIT(TIMSK, 1); // Enable compare match interrupt if needed
}

void TIM0_vidStop()
{
	// Assuming the clock bits are in the last three bits of TCCR0
//	TCCR0 &= 0xF8; // Clear the last 3 bits (CS02, CS01, CS00)
	CLR_BIT(TIMSK, 0); // Disable overflow interrupt
	CLR_BIT(TIMSK, 1); // Disable compare match interrupts
}

void TIM0_vidEnableOvfIreq(void)
{
	SET_BIT(TIMSK,0);
}
void TIM0_vidDisableOvfIreq(void)
{
	CLR_BIT(TIMSK,0);	
}

void TIM0_vidEnableCmpIreq(void)
{
	SET_BIT(TIMSK,1);
}
void TIM0_vidDisableCmpIreq(void)
{
	CLR_BIT(TIMSK,1);
}

void TIM0_vidSetCallbackOvf(pf pfCallBackCpy)
{
	TIM0_CallBack_Ovf = pfCallBackCpy ;
}
void TIM0_vidSetCallbackCmp(pf pfCallBackCpy)
{
	TIM0_CallBack_Cmp = pfCallBackCpy ;
}

void TIM0_vidSetValueTcnt(uint8 u8ValueCpy)
{
	TCNT0 = u8ValueCpy ;
}
void TIM0_vidSetValueOcr(uint8 u8ValueCpy)
{
	OCR0 = u8ValueCpy ;
}

uint8 TIM0_u8GetValueTcnt(void)
{
	return TCNT0 ;
}

void TIM0_vidDisconnectOC0(void)
{
	// Clear COM00 and COM01 to disconnect OC0
	CLR_BIT(TCCR0, 4); // COM00 Bit
	CLR_BIT(TCCR0, 5); // COM01 Bit
}

void TIM0_vidConnectOC0(void)
{
	// Set COM01 and clear COM00 to connect OC0 in non-inverted mode
	CLR_BIT(TCCR0, 4); // COM00 Bit
	SET_BIT(TCCR0, 5); // COM01 Bit
}

/*Compare match ISR*/
void __vector_10 (void) __attribute__((signal, used));
void __vector_10 (void)
{
	TIM0_CallBack_Cmp();
}

/*Overflow ISR*/
void __vector_11 (void) __attribute__((signal, used));
void __vector_11 (void)
{
	TIM0_CallBack_Ovf();
}

static void stub(void)
{
	
} 
