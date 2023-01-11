################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GIE.c \
../adc.c \
../app.c \
../dc_motor.c \
../gpio.c \
../lcd.c \
../lm35_sensor.c \
../pwm_timer0.c 

OBJS += \
./GIE.o \
./adc.o \
./app.o \
./dc_motor.o \
./gpio.o \
./lcd.o \
./lm35_sensor.o \
./pwm_timer0.o 

C_DEPS += \
./GIE.d \
./adc.d \
./app.d \
./dc_motor.d \
./gpio.d \
./lcd.d \
./lm35_sensor.d \
./pwm_timer0.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


