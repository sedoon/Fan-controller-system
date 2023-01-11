 /******************************************************************************
 *
 * Component: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ATmega16 ADC driver
 *
 * Author: SAYED IBRAHIM
 *
 *******************************************************************************/

#include "adc.h"
#include "../../LIB/common_macros.h" /* To use the macros like SET_BIT */
#include "avr/io.h" /* To use the ADC Registers */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	/* ADMUX Register Bits Description:
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 * REF1:0  = 00 Clear these two bits before setup the required reference voltage value
	 */
	ADMUX = 0;

	/* Setup the reference voltage value inside the REFS1 and REFS0 bits*/
	ADMUX |= (Config_Ptr->ref_volt << 6);/* shift left ref_volt a six digit in ADMUX register */

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable the AUTO trigger
	 * ADPS2:0 = 000 Clear these three bits before setup the required prescaler value
	 */
	ADCSRA = (1<<ADEN);

	/* Setup the prescaler value inside the ADPS2, ADPS1 and ADPS0 bits*/
	ADCSRA |= Config_Ptr->prescaler;
}

uint16 ADC_readChannel(uint8 channel_num)
{
	channel_num &= 0x07; /* Input channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX |= channel_num; /* Choose the correct channel by setting the channel number in MUX4:0 bits */

	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */

	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* Wait in loop if ADIF is zero
										until conversion is complete, ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF); /* Clear ADIF by write '1' to it :) */
	return ADC; /* Read the digital value from the data register */
}
