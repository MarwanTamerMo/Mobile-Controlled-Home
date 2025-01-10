/*
 * ADC.h
 *
 *  Created on: May 14, 2024
 *      Author: Marwan
 */

#ifndef ADC_H_
#define ADC_H_

#define ADC_CH0                      0
#define ADC_CH1                      1
#define ADC_CH2                      2
#define ADC_CH3                      3
#define ADC_CH4                      4
#define ADC_CH5                      5
#define ADC_CH6                      6
#define ADC_CH7                      7
#define ADC_CH0_DIF_CH0_GAIN_10X     8
#define ADC_CH1_DIF_CH0_GAIN_10X     9
#define ADC_CH0_DIF_CH0_GAIN_200X    10
#define ADC_CH1_DIF_CH0_GAIN_200X    11
#define ADC_CH2_DIF_CH2_GAIN_10X     12
#define ADC_CH3_DIF_CH2_GAIN_10X     13
#define ADC_CH2_DIF_CH2_GAIN_200X    14
#define ADC_CH3_DIF_CH2_GAIN_200X    15
#define ADC_CH0_DIF_CH1_GAIN_1X    	 16
#define ADC_CH1_DIF_CH1_GAIN_1X    	 17
#define ADC_CH2_DIF_CH1_GAIN_1X    	 18
#define ADC_CH3_DIF_CH1_GAIN_1X    	 19
#define ADC_CH4_DIF_CH1_GAIN_1X    	 20
#define ADC_CH5_DIF_CH1_GAIN_1X    	 21
#define ADC_CH6_DIF_CH1_GAIN_1X    	 22
#define ADC_CH7_DIF_CH1_GAIN_1X    	 23
#define ADC_CH0_DIF_CH2_GAIN_1X    	 24
#define ADC_CH1_DIF_CH2_GAIN_1X    	 25
#define ADC_CH2_DIF_CH2_GAIN_1X    	 26
#define ADC_CH3_DIF_CH2_GAIN_1X    	 27
#define ADC_CH4_DIF_CH2_GAIN_1X    	 28
#define ADC_CH5_DIF_CH2_GAIN_1X    	 29
#define ADC_BAND_GAP_CH         	 30
#define ADC_GND_CH               	 31

void ADC_vidInit(void);

void ADC_vidEnable(void);
void ADC_vidDisable(void);

void ADC_vidEnableIntReq(void);
void ADC_vidDisableIntReq(void);

void ADC_vidSelCh(uint8 u8ChNoCpy);
void ADC_vidStartConv(void);

uint16 ADC_u16ReadSync(uint8 u8ChNoCpy);

void ADC_vidSetCallBack(vidPfu16 pfCallBackCpy);

#endif /* ADC_H_ */
