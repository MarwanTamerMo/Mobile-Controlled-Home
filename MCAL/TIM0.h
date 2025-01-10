/********************************************************/
/** Description : Interface file for TIM0               */
/** Author      : Marwan Tamer                 	    	*/
/** Date        : 17 May 2024                           */
/** Version     : 1.0V                                  */
/********************************************************/

#ifndef TIM0_H
#define TIM0_H

void TIM0_vidInit(void);

void TIM0_vidConnectOC0(void);
void TIM0_vidDisconnectOC0(void);

void TIM0_vidEnableOvfIreq(void);
void TIM0_vidDisableOvfIreq(void);

void TIM0_vidEnableCmpIreq(void);
void TIM0_vidDisableCmpIreq(void);

void TIM0_vidSetCallbackOvf(pf pfCallBackCpy);
void TIM0_vidSetCallbackCmp(pf pfCallBackCpy);

void TIM0_vidSetValueTcnt(uint8 u8ValueCpy);
void TIM0_vidSetValueOcr(uint8 u8ValueCpy);

uint8 TIM0_u8GetValueTcnt(void);

#endif
