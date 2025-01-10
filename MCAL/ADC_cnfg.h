/*
 * ADC_cnfg.h
 *
 *  Created on: May 14, 2024
 *      Author: Marwan
 */

#ifndef ADC_CNFG_H_
#define ADC_CNFG_H_

#define ADC_VREF          AVCC

#define ADC_ADJ_MODE      ADC_RIGHT_ADJ

#define ADC_CH_SEL        ADC_CH3

#define ADC_TRIGGER_MODE  ADC_SINGLE_MODE

#define ADC_PRESCALLER    DIV_16


#if   	ADC_TRIGGER_MODE == ADC_AUTO_TRIGGER

#define ADC_AUTO_TRIGGER_SRC    FREE_RUNNING_SRC

#endif

#endif /* ADC_CNFG_H_ */
