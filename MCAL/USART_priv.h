/********************************************************/
/** Description : Private file for USART                */
/** Author      : Ahmed Abo Elnour                 	    */
/** Date        : 31 May 2024                           */
/** Version     : 1.0V                                  */
/********************************************************/

#ifndef USART_PRIV_H
#define USART_PRIV_H

#define USART_NORMAL_SPEED   0
#define USART_DBL_SPEED      1

#define USART_DATA_5BIT      0
#define USART_DATA_6BIT      1
#define USART_DATA_7BIT      2
#define USART_DATA_8BIT      3
#define USART_DATA_9BIT      7

#define USART_ASYNC          0
#define USART_SYNC           1


#define USART_PARITY_DISABLED  0
#define USART_PARITY_EVEN      2
#define USART_PARITY_ODD       3

#define USART_ONE_STOP_BIT     0
#define USART_TWO_STOP_BIT     1

#define USART_SEND_RISING      0
#define USART_SEND_FALLING     1

#define USART_MASTER           0
#define USART_SLAVE            1
#define USART_P2P              2


#define USART_BR_2400          207
#define USART_BR_4800          103
#define USART_BR_9600          51
#define USART_BR_14400         34
#define USART_BR_19200         25
#define USART_BR_28800         16
#define USART_BR_38400         12

#define USART_BR_2400_2X       416
#define USART_BR_4800_2X       207
#define USART_BR_9600_2X       103
#define USART_BR_14400_2X      68
#define USART_BR_19200_2X      51
#define USART_BR_28800_2X      34
#define USART_BR_38400_2X      25


/*Register*/
#define UDR     *((volatile uint8 *) 0x2C )
#define UCSRA   *((volatile uint8 *) 0x2B )
#define UCSRB   *((volatile uint8 *) 0x2A )
#define UCSRC   *((volatile uint8 *) 0x40 )
#define UBRRH   *((volatile uint8 *) 0x40 )
#define UBRRL   *((volatile uint8 *) 0x29 )

//two macro to define the function state
#define BUSY     0
#define IDLE     1

static void Stub (void);
#endif
