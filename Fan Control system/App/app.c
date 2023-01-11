/*
 ============================================================================
 Name        : APPICATION.c
 Author      : SAYED IBRAHIM
 Description : System control fan speed based on the room temperature
 Date        : 28/03/2022
 ============================================================================
 */

#include "../MCAL/ADC/adc.h"
#include "../MCAL/GPIO/gpio.h"
#include "../HAL/LCD/lcd.h"
#include "../HAL/LM35/lm35_sensor.h"
#include "../HAL/DC_MOTOR/dc_motor.h"
#include "avr/io.h" /* To use the SREG Register */
#include "../MCAL/GIE/GIE.h"
typedef enum
{
	FAN_OFF,FAN_ON
}Fan_State;

int main(void)
{
	/*set direction for lEDS*/
	GPIO_setupPinDirection(PORTA_ID,PIN3_ID,PIN_OUTPUT);/*red led*/
	GPIO_setupPinDirection(PORTA_ID,PIN4_ID,PIN_OUTPUT);/*orange led*/
	GPIO_setupPinDirection(PORTA_ID,PIN5_ID,PIN_OUTPUT);/*yellow led*/
	GPIO_setupPinDirection(PORTA_ID,PIN6_ID,PIN_OUTPUT);/*green led*/

	uint8 temp;

	ADC_ConfigType ADC_Configurations = {INTERNAL_VOLT,F_CPU_8};

	Fan_State Fan = FAN_OFF;

	/* Enable interrupts by setting I-bit */
	GIE_Enable();

	/* Initialize Motor driver */
	DcMotor_Init();

	/* Initialize LCD driver */
	LCD_init();

	/* Initialize ADC driver */
	ADC_init(&ADC_Configurations);

	/* Display this string "Temp =   C" only once on LCD at the second row*/
	LCD_moveCursor(1,4);
	LCD_displayString("Temp =    C");

    while(1)
    {
    	/* Get the temperature value */
    	temp = LM35_getTemperature();

		/* Control the duty cycle of the output PWM signal (Fan Speed) based on the temperature value */
		if(temp >= 120)/*if temperature greater than or equal 120 c open the motor with full speed */
		{
			GPIO_writePort(PORTA_ID,LOGIC_LOW);/*led off*/
			Fan = FAN_ON;
			DcMotor_Rotate(DC_MOTOR_CW,100); /* Rotates clock wise the motor with duty cycle 100% speed */
			GPIO_writePin(PORTA_ID,PIN3_ID,LOGIC_HIGH);/*red led when temperature >=120  */

		}
		else if(temp >= 90)/*if temperature greater than or equal 90 c open the motor with 75% speed */
		{
			GPIO_writePort(PORTA_ID,LOGIC_LOW);/*led off*/
			Fan = FAN_ON;
			DcMotor_Rotate(DC_MOTOR_CW,75);/* Rotates clock wise the motor with duty cycle 75% speed */
			GPIO_writePin(PORTA_ID,PIN4_ID,LOGIC_HIGH);/*orange led when temperature >=90  */
		}
		else if(temp >= 60)/*if temperature greater than or equal 60 c open the motor with 50% speed */
		{
			GPIO_writePort(PORTA_ID,LOGIC_LOW);/*led off*/
			Fan = FAN_ON;
			DcMotor_Rotate(DC_MOTOR_CW,50); /* Rotates clock wise the motor with duty cycle 50% speed */
			GPIO_writePin(PORTA_ID,PIN5_ID,LOGIC_HIGH);/*yellow led when temperature >=60  */
		}
		else if(temp >= 30)/*if temperature greater than or equal 30 c open the motor with 25% speed */
		{
			GPIO_writePort(PORTA_ID,LOGIC_LOW);/*led off*/
			Fan = FAN_ON;
			DcMotor_Rotate(DC_MOTOR_CW,25); /* Rotates clock wise the motor with duty cycle 25% speed */
			GPIO_writePin(PORTA_ID,PIN6_ID,LOGIC_HIGH);/*green led when temperature >=30  */
		}
		else/*if temperature Less than  30 c Close the motor with 0% speed */
		{
			Fan = FAN_OFF;
			DcMotor_Rotate(DC_MOTOR_STOP,0); /* Stop the motor with duty cycle 0% speed */
		}

		/* Display the temperature and FAN state */
		if(Fan == FAN_OFF)
		{
			LCD_moveCursor(0,4);
			LCD_displayString("FAN is OFF");
		}
		else
		{
			LCD_moveCursor(0,4);
			LCD_displayString("FAN is ON ");
		}
		
		/* Display the temperature value every time at same position in the second line  */
		LCD_moveCursor(1,11);
		if(temp >= 100)
		{
			LCD_intgerToString(temp);
		}
		else
		{
			LCD_intgerToString(temp);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}
    }
}
