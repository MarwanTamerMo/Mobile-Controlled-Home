#include "STD_Types.h"
#include "BIT_Math.h"
#include <util/delay.h>
#include "DIO.h"
#include "LCD.h"

// Function to jiggle "WELCOME" text on the LCD
void LCD_vidWelcomeJiggle(uint8 u8LcdIndxCpy)
{
    char* welcomeText = "WELCOME :)";
    uint8 i = 2; // To reverse direction at specific position (Change this initialization value to change starting position)
    uint8 direction = 1; // 1 for right, 0 for left
    uint8 jiggleCountLoc;

    for(jiggleCountLoc = 0; jiggleCountLoc < 10; ++jiggleCountLoc) // Jiggle 10 times
    {
        LCD_vidSendCmd(u8LcdIndxCpy, LCD_CLR);
        LCD_vidSendCmd(u8LcdIndxCpy, LCD_FIRST_LINE + i);
        LCD_vidWriteString(u8LcdIndxCpy, welcomeText); 
        
        if (direction) // Move right
        {
            i++;

            if(i == 5)
            {
                direction = 0; // Change direction to left
            }
        }
        else // Move left
        {
            i--;
            if(i == 2)
            {
                direction = 1; // Change direction to right
            }
        }

        _delay_ms(400); // Wait between movements
    }
}

// Function to animate "Loading..." with dots
void LCD_vidLoadingAnimation(uint8 u8LcdIndxCpy, char* loadingText)
{
    uint8 dotCount = 0;

    for(uint8 cycle = 0; cycle < 8; ++cycle)
    {
        LCD_vidSendCmd(u8LcdIndxCpy, LCD_CLR);
        LCD_vidSendCmd(u8LcdIndxCpy, LCD_FIRST_LINE);
        LCD_vidWriteString(u8LcdIndxCpy, loadingText); 

        // Write dots based on dotCount
        for(uint8 i = 0; i < dotCount; i++)
        {
            LCD_vidWriteData(u8LcdIndxCpy, '.');
        }

        dotCount = (dotCount + 1) % 4; // Cycle between 0, 1, 2, 3 dots
        _delay_ms(500); 
    }

    LCD_vidSendCmd(0, LCD_CLR);
}
