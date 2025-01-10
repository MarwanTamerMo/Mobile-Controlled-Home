/********************************************************/
/** Description : config file for TIM0                  */
/** Author      : Marwan Tamer                 	        */
/** Date        : 18 May 2024                           */
/** Version     : 1.0V                                  */
/********************************************************/

#ifndef TIM0_CFG_H
#define TIM0_CFG_H

#define TIM0_MODE		TIM0_FAST_PWM

#define TIM0_CLK_SEL    TIM0_PRESC_8

#define TIM0_COM_BITS   2

// For future improvements and case handling.
#define  A1  10
#define  CONC_(a,b) CONC_H_P(a,b)
#define  CONC_H_P(a,b) CONC_H_(a,b)
#define  CONC_H_(a,b) a##b


#endif 
