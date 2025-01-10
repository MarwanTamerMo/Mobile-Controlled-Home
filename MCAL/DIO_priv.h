/********************************************************/
/** Description : Private file for DIO                  */
/** Author      : Ahmed Abo Elnour                 	    */
/** Date        : 29 Mar 2024                           */
/** Version     : 1.0V                                  */
/********************************************************/

#ifndef DIO_PRIV_H
#define DIO_PRIV_H

#define INPUT 0
#define OUTPUT 1

/*ODRA === PORTA , IDRA === PINA*/
#define DDRA    *((volatile uint8 *)0x3A)
#define ODRA    *((volatile uint8 *)0x3B)
#define IDRA    *((volatile uint8 *)0x39)

#define DDRB    *((volatile uint8 *)0x37)
#define ODRB    *((volatile uint8 *)0x38)
#define IDRB    *((volatile uint8 *)0x36)

#define DDRC    *((volatile uint8 *)0x34)
#define ODRC    *((volatile uint8 *)0x35)
#define IDRC    *((volatile uint8 *)0x33)

#define DDRD    *((volatile uint8 *)0x31)
#define ODRD    *((volatile uint8 *)0x32)
#define IDRD    *((volatile uint8 *)0x30)

#define Conc(b7,b6,b5,b4,b3,b2,b1,b0)      Conc_help(b7,b6,b5,b4,b3,b2,b1,b0)
#define Conc_help(b7,b6,b5,b4,b3,b2,b1,b0) 0b##b7##b6##b5##b4##b3##b2##b1##b0


#endif
  
