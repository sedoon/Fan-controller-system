
/******************************************************************************
 * Component: GIE
 *
 * File Name: GIE.h
 *
 * Description: Source file for the ATmega16 global interrupt enable driver
 *
 * Author:SAYED IBRAHIM
 *
 *******************************************************************************/
#include "../../LIB/common_macros.h"
#include "GIE.h"
#include "avr/io.h"


void GIE_Enable(void)
{
	SET_BIT(SREG,SREG_I);
}

void GIE_Disable(void)
{
	CLEAR_BIT(SREG,SREG_I);
}
