################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/APP.c 

OBJS += \
./APP/APP.o 

C_DEPS += \
./APP/APP.d 


# Each subdirectory must supply rules for building sources it contributes
APP/%.o: ../APP/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\Micheal-Onsy\Desktop\delivery\5- I2C_Task1\MC2_EX1\MCAL\GLOBAL_INTERRUPT" -I"C:\Users\Micheal-Onsy\Desktop\delivery\5- I2C_Task1\MC2_EX1\APP" -I"C:\Users\Micheal-Onsy\Desktop\delivery\5- I2C_Task1\MC2_EX1\LIBRARY" -I"C:\Users\Micheal-Onsy\Desktop\delivery\5- I2C_Task1\MC2_EX1\MCAL\DIO" -I"C:\Users\Micheal-Onsy\Desktop\delivery\5- I2C_Task1\MC2_EX1\MCAL\I2C" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


