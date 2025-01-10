/********************************************************/
/** Description : Interface file for TIM2               */
/** Author      : Marwan Tamer                 	    */
/** Date        : 22 May 2024                            */
/** Version     : 1.0V                                  */
/********************************************************/

#ifndef TIM2_H
#define TIM2_H

void TIM2_vidInit(void);

void TIM2_vidConnectOC2(void);
void TIM2_vidDisconnectOC2(void);

void TIM2_vidEnableOvfIreq(void);
void TIM2_vidDisableOvfIreq(void);

void TIM2_vidEnableCmpIreq(void);
void TIM2_vidDisableCmpIreq(void);

void TIM2_vidSetCallbackOvf(pf pfCallBackCpy);
void TIM2_vidSetCallbackCmp(pf pfCallBackCpy);

void TIM2_vidSetValueTcnt(uint8 u8ValueCpy);
void TIM2_vidSetValueOcr(uint8 u8ValueCpy);

uint8 TIM2_u8GetValueTcnt(void);

 // 100, on : 20, off: 80
 // 50,  on: 25,  off: 25
 // 20,  on: 16,  off: 4
 // 
 // 3097 , 64


#endif
