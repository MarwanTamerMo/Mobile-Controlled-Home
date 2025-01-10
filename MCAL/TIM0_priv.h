/********************************************************/
/** Description : private file for TIM0                 */
/** Author      : Marwan Tamer                 	    	*/
/** Date        : 18 May 2024                           */
/** Version     : 1.0V                                  */
/********************************************************/

#ifndef TIM0_PRIV_H
#define TIM0_PRIV_H


#define TCCR0    *((volatile uint8 *) 0x53)
#define TCNT0    *((volatile uint8 *) 0x52)
#define OCR0     *((volatile uint8 *) 0x5C)
#define TIMSK    *((volatile uint8 *) 0x59)
#define TIFR     *((volatile uint8 *) 0x58)



#define TIM0_NORMAL             0
#define TIM0_PHASE_CORR         1
#define TIM0_CTC                2
#define TIM0_FAST_PWM           3


#define TIM0_OFF                0
#define TIM0_PRESC_1            1
#define TIM0_PRESC_8            2
#define TIM0_PRESC_64           3
#define TIM0_PRESC_256          4
#define TIM0_PRESC_1024         5
#define TIM0_EXT_FALLING        6
#define TIM0_EXT_RISING         7

static void stub(void);


#endif
