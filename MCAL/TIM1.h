/********************************************************/
/** Description : Interface file for TIM1               */
/** Author      : Ahmed Abo Elnour                 	    */
/** Date        : 17 May 2024                            */
/** Version     : 1.0V                                  */
/********************************************************/

#ifndef TIM1_H
#define TIM1_H


void TIM1_vidInit(void);
/*OverFlow INT*/
void TIM1_vidEnableOvfIreq(void);
void TIM1_vidDisableOvfIreq(void);

/*Compare match for Channel B*/
void TIM1_vidEnableCmp_BIreq(void);

void TIM1_vidDisableCmp_BIreq(void);

/*Compare match for Channel A*/
void TIM1_vidEnableCmp_AIreq(void);

void TIM1_vidDisableCmp_AIreq(void);
/*Input Capture INT */
void TIM1_vidEnableICUIreq(void);
void TIM1_vidDisableICUIreq(void);

void TIM1_vidSetCallbackOvf(pf pfCallBackCpy);
void TIM1_vidSetCallbackCmp_CHA(pf pfCallBackCpy);
void TIM1_vidSetCallbackCmp_CHB(pf pfCallBackCpy);
void TIM1_vidSetCallbackICU(pf pfCallBackCpy);

void TIM1_vidSetValueTcnt(uint16 u16ValueCpy);
void TIM1_vidSetValueOcr_A(uint16 u16ValueCpy);
void TIM1_vidSetValueOcr_B(uint16 u16ValueCpy);
void TIM1_vidSetValueIcr(uint16 u16ValueCpy);

void TIM1_vidChangeSenseICU(uint8 u8SenseCpy);

uint16 TIM1_u16GetValueTcnt(void);

uint16 TIM1_u16GetValueICR(void);







#endif
