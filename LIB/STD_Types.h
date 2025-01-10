/********************************************************/
/** Description : Standard Data types lib               */
/** Author      : Ahmed Abo Elnour                 	    */
/** Date        : 2 Mar 2024                            */
/** Version     : 2.0V                                  */
/** Update      : add Standard error Status             */
/********************************************************/

#ifndef STD_TYPES_H
#define STD_TYPES_H


typedef  	unsigned char	    uint8  ;
typedef  	unsigned short int  uint16 ;
typedef  	unsigned long  int  uint32 ;
		
typedef  	signed char     	sint8  ;
typedef  	signed short int    sint16 ;
typedef     signed long int     sint32 ;
		
typedef  	float           	float32;
typedef  	double       	    float64;
typedef  	long double         float128;

typedef enum 
{
	E_OK  ,
	E_NOK ,
	E_NOK_PARM_OUT_OF_RANGE ,
	E_NOK_PARM_NULL_POINTER 
	
	
}tenuErrorStatus;

typedef void (*pf) (void);
typedef void (*vidPfu16)(uint16);
typedef void (*vidPfu8)(uint8);

#define NULL ((void*)0)

#endif /* Gaurd */
  
