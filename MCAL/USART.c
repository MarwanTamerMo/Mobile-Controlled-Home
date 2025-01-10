#include "STD_Types.h"
#include "BIT_Math.h"

#include "USART.h"
#include "USART_cfg.h"
#include "USART_priv.h"



static pf USART_pfCallBackRxCmp = Stub ;
static pf USART_pfCallBackTxCmp = Stub ;
static pf USART_pfCallBackUdrEmp = Stub ;

static uint8 USART_SendStringFuncState = IDLE,USART_RecStringFuncState = IDLE,SendingCntr=0,ReceiveCntr=0,USART_WordSize;
static char * USART_StringSending=NULL;
static char * USART_StringReceive=NULL;


void   USART_vidInit(void)
{
	uint8 u8UBRRH_Pre = 0b00000000;
	uint8 u8UCSRB_Pre = 0b00011000;
	uint8 u8UCSRC_Pre = 0b10000000;
#if USART_SPEED_MODE ==  USART_DBL_SPEED
	SET_BIT(UCSRA,1);
#else
	CLR_BIT(UCSRA,1);	
#endif
	u8UCSRB_Pre = u8UCSRB_Pre| (USART_DATA_SIZE&0b00000100);
	u8UCSRC_Pre = u8UCSRC_Pre| (USART_CLK_MODE<<6)| (USART_PARITY_MODE<<4)|
			(USART_STOP_BITS<<3)| ((USART_DATA_SIZE &0b00000011)<<1)|
			USART_POLARITY_STS ;

#if USART_REL_MODE == USART_SLAVE
	/*DO Nothing*/
#else
	u8UBRRH_Pre = u8UBRRH_Pre|((USART_BAUD_RATE>>8)& 0b00001111);
	UBRRL = (uint8)USART_BAUD_RATE;
	UBRRH = (uint8)u8UBRRH_Pre ;
#endif
	UCSRB = u8UCSRB_Pre ;
	UCSRC = u8UCSRC_Pre ;

}
void   USART_vidSendDataSync(uint16 u16DataCpy)
{
	while(GET_BIT(UCSRA , 5)!=1); // wait udr empty for tx
#if USART_DATA_SIZE == USART_DATA_9BIT
	if (GET_BIT(u16DataCpy,8)==0)
	{
		CLR_BIT(UCSRB,0);
	}
	else
	{
		SET_BIT(UCSRB,0);
	}
	UDR =(uint8) u16DataCpy ;
#else
	UDR =(uint8) u16DataCpy ;


#endif
}
void   USART_vidEnableRecvCmpIreq(void)
{
	SET_BIT(UCSRB, 7);
}
void   USART_vidDisableRecvCmpIreq(void)
{
	CLR_BIT(UCSRB, 7);
}
void   USART_vidEnableTxCmpIreq(void)
{
	SET_BIT(UCSRB, 6);
}
void   USART_vidDisableTxCmpIreq(void)
{
	CLR_BIT(UCSRB, 6);
}
void   USART_vidEnableUdrEmpIreq(void)
{
	SET_BIT(UCSRB, 5);
}
void   USART_vidDisableUdrEmpIreq(void)
{
	CLR_BIT(UCSRB, 5);
}
void   USART_vidEnableRxChannel(void)
{
	SET_BIT(UCSRB, 4);
}
void   USART_vidDisableRxChannel(void)
{
	CLR_BIT(UCSRB, 4);
}
void   USART_vidEnableTxChannel(void)
{
	SET_BIT(UCSRB, 3);
}
void   USART_vidDisableTxChannel(void)
{
	CLR_BIT(UCSRB, 3);
}
void   USART_vidSetCallBackRxCmp(pf pfCallbackCpy)
{
	USART_pfCallBackRxCmp = pfCallbackCpy ;
}
void   USART_vidSetCallBackTxCmp(pf pfCallbackCpy)
{
	USART_pfCallBackTxCmp = pfCallbackCpy;
}
void   USART_vidSetCallBackUdrEmp(pf pfCallbackCpy)
{
	USART_pfCallBackUdrEmp = pfCallbackCpy ;
}
void   USART_vidWriteTxDataReg(uint16 u16DataCpy)
{
#if USART_DATA_SIZE == USART_DATA_9BIT
	if (GET_BIT(u16DataCpy,8)==0)
	{
		CLR_BIT(UCSRB,0);
	}
	else
	{
		SET_BIT(UCSRB,0);
	}
	UDR =(uint8) u16DataCpy ;	
#else
	UDR =(uint8) u16DataCpy ;
#endif
}
uint16 USART_u16ReadRxDataReg(void)
{
	uint16 u16VarLoc = 0 ;

#if USART_DATA_SIZE == USART_DATA_9BIT
	u16VarLoc = GET_BIT(UCSRB,1);
	u16VarLoc = (u16VarLoc<<8)|UDR ;
#else
	u16VarLoc = UDR ;
#endif
	return u16VarLoc ;
}
uint16 USART_u16RecvDataSync(void)
{
	uint16 u16VarLoc = 0 ;
	/*The concept of TIMEOut should be implemented here to avoid any HW failure
	using MACRO #define TIMEOUT 50000 for example and may be configurable
	 then the condition will be  while((GET_BIT(UCSRA , 7)!=1) && (counter <TIMEOUT))
	inside the while loop counter++; after that check if the loop broke due to which condition
	and based on that assign to the register or return Error status*/
	while(GET_BIT(UCSRA , 7)!=1); // wait Rx rec data

#if USART_DATA_SIZE == USART_DATA_9BIT
	u16VarLoc = GET_BIT(UCSRB,1);
	u16VarLoc = (u16VarLoc<<8)|UDR ;
#else
		u16VarLoc = UDR ;

#endif

	SET_BIT(UCSRA,7);
	return 	u16VarLoc ;
}
uint8  USART_u8ReadErrFlgs(void)
{
	return ((UCSRA>>2)& 0b00000111);
}

// Rx Complete
//this function is used to implement the receive string Asynchrounous
void __vector_13 (void) __attribute__((signal,used));
void __vector_13 (void)
{
	/*This function will be called every time the Receiving is completed */
	/*1. Assign UDR data into the Receiver string*/
	USART_StringReceive[ReceiveCntr]=UDR;
	ReceiveCntr++;
	if (ReceiveCntr==USART_WordSize)
	{
		/*2. make the function IDLE Again*/
		USART_RecStringFuncState=IDLE;
		/*3.Disable the interrupt*/
		USART_vidDisableRecvCmpIreq();
		/*4.Invoke the call back function*/
		USART_pfCallBackRxCmp();
	}
}

//UDR Empty.
//this function is used in send asynch string
void __vector_14 (void) __attribute__((signal,used));
void __vector_14 (void)
{
	/*this function will be called every time the UDR is empty so it's ready to get a new data*/
	/*1.  Assign the current element of the array(string) into the UDR and increment the sending counter*/


	UDR=USART_StringSending[SendingCntr];
	SendingCntr++;
	/*1.1 Check if the string achieved the \0 or not */
	if (USART_StringSending[SendingCntr]=='\0')
	{
		/*2. make the function IDLE Again*/
		USART_SendStringFuncState=IDLE;
		/*3.Disable the interrupt*/
		USART_vidDisableUdrEmpIreq();
		/*4.Invoke the call back function*/
		USART_pfCallBackUdrEmp();

	}

}


//Tx complete
void __vector_15 (void) __attribute__((signal,used));
void __vector_15 (void)
{

	USART_pfCallBackTxCmp();
}

static void Stub (void)
{

}


void USART_vidSendStringSynch(const char * charStrCpy)
{

	// Send a null character to clear previous data in data buffer (register)
	USART_vidSendDataSync('\0');

	uint16 u16CntrLoc = 0;

	while (charStrCpy[u16CntrLoc] != '\0')
	{
		//USART_vidSendDataSync(charStrCpy[u16CntrLoc]);
		USART_vidSendDataSync(charStrCpy[u16CntrLoc]);
		u16CntrLoc++;
	}

}


void USART_vidSendStringAsynch(char* charStrCpy, pf pfNotificationFunc)
{
	/*0.0 Check if the Function is BUSY or not*/
	if (USART_SendStringFuncState==IDLE)
	{
		/*1. Check if the pointers != NULL*/
		if ((charStrCpy== NULL) || (pfNotificationFunc==NULL))
		{
			/*should return error status */
		}
		else
		{
			/*0.1 Make the function state busy and will convert again to idle by the ISR*/
			USART_SendStringFuncState=BUSY;
			/*1. initiate the variables Globally*/
			USART_StringSending=charStrCpy;
			USART_pfCallBackUdrEmp=pfNotificationFunc;
			/*2. Enable the UDR empty Interrupt request*/
			USART_vidEnableUdrEmpIreq();
		}

	}
	else
	{
		/*Function is busy*/
	}
}
void USART_vidReceiveWordSynch(char* pcharDataCpy,uint8 u8WordSizeCpy)
{
	uint8 u8cntrLoc=0;

	for(u8cntrLoc=0 ; u8cntrLoc< u8WordSizeCpy ; u8cntrLoc++)
	{
		pcharDataCpy[u8cntrLoc]=(uint8)USART_u16RecvDataSync();

	}
}

void USART_vidReceiveWordAsynch(char* pcharWordCpy ,uint8 u8WordSizeCpy ,pf pfNotificationFunc)
{
	/*0.0 Check if the Function is BUSY or not*/
	if (USART_RecStringFuncState==IDLE)
	{
		/*1. Check if the pointers != NULL*/
		if ((pcharWordCpy== NULL) || (pfNotificationFunc==NULL))
		{
			/*should return error status */
		}
		else
		{
			/*0.1 Make the function state busy and will convert again to idle by the ISR*/
			USART_SendStringFuncState=BUSY;
			/*1. initiate the variables Globally*/
			USART_StringReceive=pcharWordCpy;
			USART_WordSize=u8WordSizeCpy;
			USART_pfCallBackRxCmp=pfNotificationFunc;
			/*2. Enable the UDR empty Interrupt request*/
			USART_vidEnableRecvCmpIreq();
		}

	}
	else
	{
		/*Function is busy*/
	}

}
