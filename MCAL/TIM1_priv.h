/********************************************************/
/** Description : private file for TIM1                 */
/** Author      : Ahmed Abo Elnour                 	    */
/** Date        : 18 May 2024                           */
/** Version     : 1.0V                                  */
/********************************************************/

#ifndef TIM1_PRIV_H
#define TIM1_PRIV_H

#define TIMSK     *((volatile uint8 *) 0x59 )
#define TIFR      *((volatile uint8 *) 0x58 )
#define TCCR1A    *((volatile uint8 *) 0x4F )
#define TCCR1B    *((volatile uint8 *) 0x4E )
#define TCNT1H	  *((volatile uint8 *) 0x4D )
#define TCNT1L	  *((volatile uint8 *) 0x4C )
#define OCR1AH    *((volatile uint8 *) 0x4B )
#define OCR1AL    *((volatile uint8 *) 0x4A )
#define OCR1BH    *((volatile uint8 *) 0x49 )
#define OCR1BL    *((volatile uint8 *) 0x48 )
#define ICR1H     *((volatile uint8 *) 0x47 )
#define ICR1L     *((volatile uint8 *) 0x46 )




#define TIM1_NORMAL             	    0
#define TIM1_PHASE_CORR_8bit            1
#define TIM1_PHASE_CORR_9bit            2
#define TIM1_PHASE_CORR_10bit           3
#define TIM1_CTC_OCR_TOP                4
#define TIM1_FAST_PWM_8bit              5
#define TIM1_FAST_PWM_9bit              6
#define TIM1_FAST_PWM_10bit             7
#define TIM1_PHASE_FREQ_CORR_ICR1_TOP   8
#define TIM1_PHASE_FREQ_CORR_OCR1A_TOP  9
#define TIM1_PHASE_CORR_ICR1_TOP        10
#define TIM1_PHASE_CORR_OCR1A_TOP       11
#define TIM1_CTC_ICR1_TOP               12
#define TIM1_FAST_PWM_ICR1_TOP          14
#define TIM1_FAST_PWM_OCR1A_TOP         15

/*Clock select*/

#define TIM1_OFF                    	 0
#define TIM1_PRESC_1            		 1
#define TIM1_PRESC_8           	    	 2
#define TIM1_PRESC_64           		 3
#define TIM1_PRESC_256          		 4
#define TIM1_PRESC_1024         		 5
#define TIM1_EXT_FALLING        		 6
#define TIM1_EXT_RISING         		 7

/*for ctc mode COM bits Selection  */


#define TIM1_OC1_STS_DISC 		    0
#define TIM1_OC1_STS_TGL			1
#define TIM1_OC1_STS_CLR			2
#define TIM1_OC1_STS_SET			3



/*for fast-PWM */

#define TIM1_OC1_STS_NON_INV      2
#define TIM1_OC1_STS_INV		  3


/*for Phase correct */
#define TIM1_OC1_STS_CLR_UP		  2
#define TIM1_OC1_STS_SET_UP		  3

/*Noise Canceler */
#define TIM1_NC_ON	              1
#define TIM1_NC_OFF				  0

/*Edge Select*/
#define TIM1_EDGSELEC_FAL		  0
#define TIM1_EDGSELEC_RIS		  1


static void stub(void);


#endif 
