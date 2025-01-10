
#include "STD_Types.h"

#include "LCD_cfg.h"
#include "LCD_priv.h"



const tstrLcdcfg LCD_astrConfigSet[LCD_MAX_NUM] = 
{
	/*All internal and external cfg for lcd indx 0*/
	{
		/*All internal cfg for lcd */
		{
			/* N_Line    , Font         , Display         ,*/
			LCD_TWO_LINE , LCD_FONT_5X7 , LCD_DISPLAY_ON ,
			
			/* Cursor      , C_Blink             , EntryMode   , Shift*/
			LCD_CURSOR_OFF ,LCD_CURSOR_BLINK_OFF , LCD_LTR     ,  LCD_DISPLAY_SHIFT_OFF
		}
		,
		/*All external cfg for lcd */
		{
			/*ConcMode      , Rs  ,  Rw  ,  En  */
			LCD_4BIT_MODE   , 16  ,  17  , 18   ,
			
			/*           DataBus                */
			/*D0 , D1 , D2 ,D3 ,D4 ,D5 , D6 ,D7 */
			{ 0, 0, 0, 0, 19 ,20 ,21, 22 }
			
		}
		
	}
	
// (Under development)

//	/*All internal and external cfg for lcd indx 1*/
//	{
//			/*All internal cfg for lcd */
//			{
//				/* N_Line    , Font         , Display         ,*/
//				LCD_TWO_LINE , LCD_FONT_5X7 , LCD_DISPLAY_ON ,
//
//				/* Cursor      , C_Blink             , EntryMode   , Shift*/
//				LCD_CURSOR_OFF ,LCD_CURSOR_BLINK_OFF , LCD_LTR     ,  LCD_DISPLAY_SHIFT_OFF
//			}
//			,
//			/*All external cfg for lcd */
//			{
//				/*ConcMode      , Rs  ,  Rw  ,  En  */
//				LCD_4BIT_MODE   ,  0  ,  1  ,    2   ,
//
//				/*           DataBus                */
//				/*D0 , D1 , D2 ,D3 ,D4 ,D5 , D6 ,D7 */
//				{ 0 , 0, 0 , 0 , 4 , 5, 6 ,7 }
//
//			}
//
//	}

	
};

