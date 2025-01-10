/********************************************************/
/** Description : Interface file for DIO                */
/** Author      : Ahmed Abo Elnour                 	    */
/** Date        : 29 Mar 2024                           */
/** Version     : 1.0V                                  */
/********************************************************/

#ifndef DIO_H
#define DIO_H  


void DIO_vidInit(void); // DIR
/********************************************************/
/*u8PinNumCpy: 0--7 (A)  8--15 (B) 16 --23 (C)24--31 (D)*/
/********************************************************/
tenuErrorStatus DIO_enuWritePin(uint8 u8PinNumCpy , uint8 u8PinValCpy); // OUTPUT VALUE

tenuErrorStatus DIO_enuReadPin(uint8 u8PinNumCpy , uint8 * pu8PinValCpy); // Get Pin value

tenuErrorStatus DIO_enuActivPull(uint8 u8PinNumCpy, uint8 u8ResStatscpy); //Activate pull-up Resistor
#endif