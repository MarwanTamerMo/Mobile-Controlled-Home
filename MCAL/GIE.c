#include "STD_Types.h"
#include "BIT_Math.h"

#include "GIE.h"

#define SREG  *((volatile uint8 *) 0x5F)

void GIE_vidEnable(void)
{
	SET_BIT(SREG , 7 );
}
void GIE_vidDisable(void)
{
	CLR_BIT(SREG , 7 );
}