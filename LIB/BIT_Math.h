/********************************************************/
/** Description : Bit Manibulation lib                  */
/** Author      : Ahmed Abo Elnour                 	    */
/** Date        : 8 Mar 2024                            */
/** Version     : 1.0V                                  */
/********************************************************/

#ifndef BIT_MATH_H
#define BIT_MATH_H    

#define SET_BIT(Reg,BitNo)       (Reg) = (Reg) |  (1<< (BitNo))
#define CLR_BIT(Reg,BitNo)       (Reg) = (Reg) & ~(1<< (BitNo))
#define TGL_BIT(Reg,BitNo)       (Reg) = (Reg) ^  (1<< (BitNo))
#define GET_BIT(Reg,BitNo)       (((Reg)>>(BitNo))& 0x01)

#define CLEAR_BIT(Reg,BitNo)       (Reg) = (Reg) & ~(1<< (BitNo))

#endif /*gaurd*/



