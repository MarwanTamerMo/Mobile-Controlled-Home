/********************************************************/
/** Description : Interface file for USART              */
/** Author      : Ahmed Abo Elnour                 	    */
/** Date        : 31 May 2024                           */
/** Version     : 1.0V                                  */
/********************************************************/

#ifndef USART_H
#define USART_H

void   USART_vidInit(void);
void   USART_vidSendDataSync(uint16 u16DataCpy);
void   USART_vidEnableRecvCmpIreq(void);
void   USART_vidDisableRecvCmpIreq(void);
void   USART_vidEnableTxCmpIreq(void);
void   USART_vidDisableTxCmpIreq(void);
void   USART_vidEnableUdrEmpIreq(void);
void   USART_vidDisableUdrEmpIreq(void);
void   USART_vidEnableRxChannel(void);
void   USART_vidDisableRxChannel(void);
void   USART_vidEnableTxChannel(void);
void   USART_vidDisableTxChannel(void);
void   USART_vidSetCallBackRxCmp(pf pfCallbackCpy);
void   USART_vidSetCallBackTxCmp(pf pfCallbackCpy);
void   USART_vidSetCallBackUdrEmp(pf pfCallbackCpy);
void   USART_vidWriteTxDataReg(uint16 u16DataCpy);
uint16 USART_u16ReadRxDataReg(void);
uint16 USART_u16RecvDataSync(void);
uint8  USART_u8ReadErrFlgs(void);

void USART_vidSendStringSynch(const char * charStrCpy);
void USART_vidSendStringAsynch( char* charStrCpy,pf pfNotificationFunc );
/*These functions should be passed the >EXACT< number of char in the passed string*/
//cuz if more than the exact number, send sync or asynch functions will not send the '\0' which will
//make this function stuck in the while loop waiting for the flag
void USART_vidReceiveWordSynch(char* pcharDataCpy,uint8 u8WordSizeCpy);
void USART_vidReceiveWordAsynch(char* pcharWordCpy ,uint8 u8WordSizeCpy ,pf pfNotificationFunc);



#endif
