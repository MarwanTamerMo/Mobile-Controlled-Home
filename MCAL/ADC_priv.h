/*
 * ADC_priv.h
 *
 *  Created on: May 14, 2024
 *      Author: Marwan
 */

#ifndef ADC_PRIV_H
#define ADC_PRIV_H

#define ADC_RIGHT_ADJ   0
#define ADC_LEFT_ADJ    1

#define AREF    0
#define AVCC    1
#define INT2_56 3

#define ADC_SINGLE_MODE  0
#define ADC_AUTO_TRIGGER 1

#define DIV_2   1
#define DIV_4   2
#define DIV_8   3
#define DIV_16  4
#define DIV_32  5
#define DIV_64  6
#define DIV_128 7

#define FREE_RUNNING_SRC  0
#define ANALOG_CMP_SRC    1
#define EXT0_SRC          2
#define TIM0_CMP_SRC	  3
#define TIM0_OVF_SRC	  4
#define TIM1_CMP_SRC	  5
#define TIM1_OVF_SRC	  6
#define TIM1_ICU_SRC	  7

static void ADC_Stub (uint16 x);

#define ADMUX   *((volatile uint8 *) 0x27)
#define ADCSRA  *((volatile uint8 *) 0x26)
#define ADCL    *((volatile uint8 *) 0x24)
#define ADCH    *((volatile uint8 *) 0x25)
#define SFIOR   *((volatile uint8 *) 0x50)


#endif /* ADC_PRIV_H_ */
