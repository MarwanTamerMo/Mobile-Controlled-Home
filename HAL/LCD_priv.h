/********************************************************/
/** Description : private file for LCD                  */
/** Author      : Ahmed Abo Elnour                 	    */
/** Date        : 5 April 2024                          */
/** Version     : 1.0V                                  */
/********************************************************/

#ifndef LCD_PRIV_H
#define LCD_PRIV_H

#define LCD_ONE_LINE 0
#define LCD_TWO_LINE 1

#define LCD_FONT_5X7   0
#define LCD_FONT_5X11  1

#define LCD_DISPLAY_OFF  0
#define LCD_DISPLAY_ON   1


#define LCD_CURSOR_OFF  0
#define LCD_CURSOR_ON   1

#define LCD_CURSOR_BLINK_OFF  0
#define LCD_CURSOR_BLINK_ON   1

#define LCD_RTL   0
#define LCD_LTR   1

#define LCD_DISPLAY_SHIFT_OFF  0
#define LCD_DISPLAY_SHIFT_ON   1


#define LCD_4BIT_MODE   0
#define LCD_8BIT_MODE   1

typedef struct 
{
	uint8 N_Line     : 1 ; 
	uint8 Font       : 1 ;
	uint8 Display    : 1 ;
	uint8 Cursor     : 1 ;
	uint8 C_Blink    : 1 ;
	uint8 EntryMode  : 1 ;
	uint8 Shift      : 1 ; 
	
}tstrLcdIntCfg ;

typedef struct
{
	uint8 ConcMode ;
	uint8 Rs ;
	uint8 Rw ;
	uint8 En ;
	uint8 DataBus[8];
}tstrLcdExtCfg ;

typedef struct 
{
	tstrLcdIntCfg strLcdIntCfg ;
	tstrLcdExtCfg strLcdExtCfg ;
	
}tstrLcdcfg ;

extern const tstrLcdcfg LCD_astrConfigSet[LCD_MAX_NUM];




#endif