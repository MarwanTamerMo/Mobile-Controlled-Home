/********************************************************/
/** Description : config file for TIM1                  */
/** Author      : Ahmed Abo Elnour                 	    */
/** Date        : 18 May 2024                           */
/** Version     : 1.0V                                  */
/********************************************************/

#ifndef TIM1_CFG_H
#define TIM1_CFG_H

#define TIM1_MODE            TIM1_FAST_PWM_ICR1_TOP

#define TIM1_NC 		     TIM1_NC_OFF

#define TIM1_EDG_SLCT        TIM1_EDGSELEC_FAL


#define TIM1_CLK_SEL         TIM1_PRESC_8

#define TIM1_COM_BITS_CHA    TIM1_OC1_STS_NON_INV
#define TIM1_COM_BITS_CHB    TIM1_OC1_STS_NON_INV


#endif 
