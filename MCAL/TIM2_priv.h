/********************************************************/
/** Description : private file for TIM2                 */
/** Author      : Marwan Tamer                  	    */
/** Date        : 22 May 2024                           */
/** Version     : 1.0V                                  */
/********************************************************/

#ifndef TIM2_PRIV_H
#define TIM2_PRIV_H


#define TCCR2    *((volatile uint8 *) 0x45)
#define TCNT2    *((volatile uint8 *) 0x44)
#define OCR2     *((volatile uint8 *) 0x43)
#define TIMSK    *((volatile uint8 *) 0x59)
#define TIFR     *((volatile uint8 *) 0x58)



#define TIM2_NORMAL             0
#define TIM2_PHASE_CORR         1
#define TIM2_CTC                2
#define TIM2_FAST_PWM           3


#define TIM2_OFF                0
#define TIM2_PRESC_1            1
#define TIM2_PRESC_8            2
#define TIM2_PRESC_64           3
#define TIM2_PRESC_256          4
#define TIM2_PRESC_1024         5
#define TIM2_EXT_FALLING        6
#define TIM2_EXT_RISING         7


static void stub(void);


#endif 