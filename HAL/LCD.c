#include "STD_Types.h"
#include "BIT_Math.h"
#include <util/delay.h>

#include "DIO.h"

#include "LCD.h"
#include "LCD_cfg.h"
#include "LCD_priv.h"

static void LCD_vidEnableFunc(uint8 u8ConMode,uint8  u8LcdIndxCpy,uint8 u8DataorCmdCpy ); /** added function **/

static void Helper(uint8 u8LcdIndxCpy , uint8 u8DataorCmdCpy);
uint8 LCD_u84BitModFlg = 0 ;
void LCD_vidInit(void) 
{
	uint8 u8CntrLoc=0;
	uint8 u8CmdLoc ;
	for(u8CntrLoc = 0 ;u8CntrLoc< LCD_MAX_NUM ; u8CntrLoc++)
	{
		if (LCD_astrConfigSet[u8CntrLoc].strLcdExtCfg.ConcMode == LCD_8BIT_MODE)
		{
			_delay_ms(30);
			          
			u8CmdLoc = 0b00110000|
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCfg.N_Line)<<3|
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCfg.Font)<<2;
			
			LCD_vidSendCmd(u8CntrLoc , u8CmdLoc);
			
			_delay_ms(2);
			
			u8CmdLoc = 0b00001000|
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCfg.Display)<<2|
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCfg.Cursor)<<1 |
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCfg.C_Blink);
			LCD_vidSendCmd(u8CntrLoc , u8CmdLoc);
			
			_delay_ms(2);
			
			LCD_vidSendCmd(u8CntrLoc , 0x01);
			
			_delay_ms(2);
			
			u8CmdLoc = 0b00000100|
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCfg.EntryMode)<<1|
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCfg.Shift);
			LCD_vidSendCmd(u8CntrLoc , u8CmdLoc);
			
			_delay_ms(2);

		}
		else
		{
			LCD_vidSendCmd(u8CntrLoc , 0b00100010);
			LCD_u84BitModFlg = 1;
			// send 0bNF00
			u8CmdLoc = 0b00000000|
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCfg.N_Line)<<7|
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCfg.Font)<<6;
			LCD_vidSendCmd(u8CntrLoc , u8CmdLoc);
			LCD_u84BitModFlg = 0;
			_delay_ms(2);
			
			u8CmdLoc = 0b00001000|
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCfg.Display)<<2|
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCfg.Cursor)<<1 |
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCfg.C_Blink);
			LCD_vidSendCmd(u8CntrLoc , u8CmdLoc);
			
			_delay_ms(2);
			
			LCD_vidSendCmd(u8CntrLoc , 0x01);
			
			_delay_ms(2);
			
			u8CmdLoc = 0b00000100|
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCfg.EntryMode)<<1|
			(LCD_astrConfigSet[u8CntrLoc].strLcdIntCfg.Shift);
			LCD_vidSendCmd(u8CntrLoc , u8CmdLoc);
			
			_delay_ms(2);
			
		}
		
	}
	
}

void LCD_vidSendCmd(uint8 u8LcdIndxCpy , uint8 u8CmdCpy)
{
	DIO_enuWritePin(LCD_astrConfigSet[u8LcdIndxCpy].strLcdExtCfg.Rs,0); 
	Helper(u8LcdIndxCpy , u8CmdCpy);
}

void LCD_vidWriteData(uint8 u8LcdIndxCpy , uint8 u8DataCpy)
{
	DIO_enuWritePin(LCD_astrConfigSet[u8LcdIndxCpy].strLcdExtCfg.Rs,1);
	Helper(u8LcdIndxCpy, u8DataCpy);
}

static void Helper(uint8 u8LcdIndxCpy , uint8 u8DataorCmdCpy)
{
    
	/*uint8 u8PinNumLoc ;*/
	if (LCD_astrConfigSet[u8LcdIndxCpy].strLcdExtCfg.ConcMode == LCD_8BIT_MODE)
	{
		 DIO_enuWritePin(LCD_astrConfigSet[u8LcdIndxCpy].strLcdExtCfg.Rw,0);
		 
		LCD_vidEnableFunc(LCD_8BIT_MODE,u8LcdIndxCpy,u8DataorCmdCpy );
	}
	else
	{
		 
		 DIO_enuWritePin(LCD_astrConfigSet[u8LcdIndxCpy].strLcdExtCfg.Rw,0);
		 
	
		 if (LCD_u84BitModFlg == 1)
		 {	/*So it's called from Init Func*/
	 
			 /*High Part*/
			LCD_vidEnableFunc(LCD_4BIT_MODE,u8LcdIndxCpy,u8DataorCmdCpy );
		 }
		 else
		 {
			 /*High Part*/
			LCD_vidEnableFunc(LCD_4BIT_MODE,u8LcdIndxCpy,u8DataorCmdCpy );
			 
			  /*Low Part*/
			 u8DataorCmdCpy = u8DataorCmdCpy<<4 ; /*To act on the second part of the cmd */
			 
			 LCD_vidEnableFunc(LCD_4BIT_MODE,u8LcdIndxCpy,u8DataorCmdCpy );
		 }
		
	}
	
}

static void LCD_vidEnableFunc(uint8 u8ConMode,uint8  u8LcdIndxCpy,uint8 u8DataorCmdCpy)

{
	uint8 u8Start=0,u8PinNumLoc;
	if (u8ConMode==LCD_4BIT_MODE)  /*	It's 4 bit mode, so the loop should start from 4 */
	{
		u8Start=4;
	}

	
	DIO_enuWritePin(LCD_astrConfigSet[u8LcdIndxCpy].strLcdExtCfg.En,1); 
	
		for(u8PinNumLoc = u8Start ; u8PinNumLoc<=7 ;u8PinNumLoc++)
		{
			DIO_enuWritePin(
				LCD_astrConfigSet[u8LcdIndxCpy].strLcdExtCfg.DataBus[u8PinNumLoc],
				GET_BIT(u8DataorCmdCpy,u8PinNumLoc)); 
		}
		_delay_ms(2);
		DIO_enuWritePin(LCD_astrConfigSet[u8LcdIndxCpy].strLcdExtCfg.En,0);
		_delay_ms(2);
	
}

void LCD_vidWriteString(uint8 u8LcdIndxCpy,char* charSTring )
{
	uint8 u8cntr=0;
	while (charSTring[u8cntr]!='\0')
	{
		LCD_vidWriteData(u8LcdIndxCpy,charSTring[u8cntr]);
		u8cntr++;
	}
}

void LCD_vidCGRAMWrite(uint8* pu8PatternArray, uint8 u8LCDIndx, uint8 u8PatternSlot)
{
	uint8 u8CntrLoc,u8Adress;
	/*In data sheet the the CGRAM address is 0001AC5---AC0
	so it's needed to make the 6th bit 1 and add the rest of the address, 
	so that 64(ob0100 0000) is added 
	
	Can be made by make Setting the 6th bit in the address too
	*/
	u8Adress=(u8PatternSlot*8)+64;

/* to make AC points to the CGRAM address before writting on it */
	LCD_vidSendCmd(u8LCDIndx,u8Adress);
	
	/*Writting the data of CGRAM */
	for (u8CntrLoc=0 ; u8CntrLoc<8 ; u8CntrLoc ++)
	{
		LCD_vidWriteData(u8LCDIndx,pu8PatternArray[u8CntrLoc]);
	}

}

void LCD_vidWriteNumber(uint8 u8LCDIndx,uint32 u32NumberCpy) /*this function takes the number right away not the ascii value*/
{
	/*
	input number ex: 1234
	1234/10 =123 , 1234%10= 4
	*/
	uint8 u8CntrLoc=0,au8ModArray[15];
	sint8 u8IteratorLoc;
	uint32 u32ResultLoc,NumberHolderLoc=u32NumberCpy;

	if (u32NumberCpy==0)
	{
		NumberHolderLoc=0;
		au8ModArray[u8CntrLoc]=0;
		LCD_vidWriteData(u8LCDIndx,(au8ModArray[u8CntrLoc]+48));
	}
	else
	{
		while (NumberHolderLoc!=0)
		{
			/*Get first digit of the number* */
			u32ResultLoc=NumberHolderLoc%10;
			/*push first digit into the array * */
			au8ModArray[u8CntrLoc]=u32ResultLoc;
			/*Update the input value by neglecting the last digit the pushed to the array*/
			NumberHolderLoc=NumberHolderLoc/10;
			u8CntrLoc++;
		}

		for(u8IteratorLoc=u8CntrLoc-1 ; u8IteratorLoc>=0; u8IteratorLoc--)
		{
			/*48 is added cuz it's the starting address of the ASCII Numbers 0--9*/
			LCD_vidWriteData(u8LCDIndx,(au8ModArray[u8IteratorLoc]+48));

		}
	}
}


void GOTOXY(uint8 u8LcdIndxCpy , uint8 u8X, uint8 u8Y)
{
	/**
	 *  imagine that he grid is like that
	 *                                    _____________________________
	 * 1st line address =0X80 or 128     |__X0,Y0_|__X0,Y1___|____|_____|
	 * 2nd line address= 0XC0 or 192     |__X1,Y0_|__X1,Y1___|____|_____|
	 *                                   |
	 *                                   |
	 * Setting DDRAM address as Data sheet is by Rs =0 , Rw=0 , DB7=1 then the rest of the 8 bits
	 * so based on that it will be always 0b1------- then the following 7 bits based on the position
	 * thus the address of the first grid is 0 + 128 which is 0b10000000
	 *and the the first grid in the second line is the same but the difference is 64  so it's 0+128+64 .
	 
	 and the LCD_first and second lines macros can be used instead of the numbers also .
	 * */
	uint8 u8AddressCpy;
	if (u8X==0)
	{
		u8AddressCpy=(u8Y)+128;
	}


	else if (u8X==1)
	{
		u8AddressCpy=u8Y+192;
	}
	LCD_vidSendCmd(	u8LcdIndxCpy,(u8AddressCpy));
}
