/********************************************************/
/** Description : Interface file for LCD                */
/** Author      : Ahmed Saeed                    	    */
/** Date        : 5 April 2024                          */
/** Version     : 1.0V                                  */
/********************************************************/

#ifndef LCD_H
#define LCD_H


#define LCD_CLR 0x01
#define LCD_FIRST_LINE 0x80
#define LCD_SECOND_LINE 0xC0

void LCD_vidInit(void) ;
void LCD_vidSendCmd(uint8 u8LcdIndxCpy , uint8 u8CmdCpy);
void LCD_vidWriteData(uint8 u8LcdIndxCpy , uint8 u8DataCpy);
void LCD_vidWriteString(uint8 u8LcdIndxCpy,char* charSTring );
void LCD_vidWriteNumber(uint8 u8LCDIndx,uint32 u32NumberCpy); /*this function takes the number right away not the ascii value*/
void LCD_vidCGRAMWrite(uint8* pu8PatternArray, uint8 u8LCDIndx, uint8 u8PatternSlot);

void GOTOXY(uint8 u8LcdIndxCpy , uint8 u8X, uint8 u8Y);

#endif

