 /******************************************************************************
 *
 * Component: ADC
 *
 * File Name: adc.h
 *
 * Description: header file for the ATmega16 ADC driver
 *
 * Author: SAYED IBRAHIM
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "../../LIB/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	AREF_VOLT,		/*REFS1(0) REFS0(0)*/
	AVCC_VOLT,		/*REFS1(0) REFS0(1)*/
	RESERVED,		/*REFS1(1) REFS0(0)*/
	INTERNAL_VOLT 	/*REFS1(1) REFS0(1)*/
}ADC_ReferenceVolatge;

typedef enum
{
	F_CPU_2,			/*ADPS2(0) ADPS1(0) ADPS0(0)*/
	F_CPU_2_AGAIN,		/*ADPS2(0) ADPS1(0) ADPS0(1)*/
	F_CPU_4,			/*ADPS2(0) ADPS1(1) ADPS0(0)*/
	F_CPU_8,			/*ADPS2(0) ADPS1(1) ADPS0(1)*/
	F_CPU_16,			/*ADPS2(1) ADPS1(0) ADPS0(0)*/
	F_CPU_32,			/*ADPS2(1) ADPS1(0) ADPS0(1)*/
	F_CPU_64,			/*ADPS2(1) ADPS1(1) ADPS0(0)*/
	F_CPU_128			/*ADPS2(1) ADPS1(1) ADPS0(1)*/
}ADC_Prescaler;

typedef struct
{
	ADC_ReferenceVolatge ref_volt;
	ADC_Prescaler prescaler;
}ADC_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Function responsible for initialize the ADC driver:
 * 1. Setup the ADC reference voltage.
 * 2. Setup the ADC prescaler.
 */
void ADC_init(const ADC_ConfigType * Config_Ptr);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 channel_num);

#endif /* ADC_H_ */
