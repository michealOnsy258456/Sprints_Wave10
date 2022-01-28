################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../main.c 

OBJS += \
./main.o 

C_DEPS += \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\Micheal-Onsy\Desktop\delivery\4- SPI_Task2\MC2\LIBRARY" -I"C:\Users\Micheal-Onsy\Desktop\delivery\4- SPI_Task2\MC2\MCAL\DIO" -I"C:\Users\Micheal-Onsy\Desktop\delivery\4- SPI_Task2\MC2\MCAL\SPI" -I"C:\Users\Micheal-Onsy\Desktop\delivery\4- SPI_Task2\MC2\MCAL\UART" -I"C:\Users\Micheal-Onsy\Desktop\delivery\4- SPI_Task2\MC2\APP" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


