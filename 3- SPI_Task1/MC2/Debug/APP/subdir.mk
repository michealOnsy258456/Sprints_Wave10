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
	avr-gcc -I"E:\sprints workshop\Sprint6\delivery\3- SPI_Task1\MC2\APP" -I"E:\sprints workshop\Sprint6\delivery\3- SPI_Task1\MC2\HAL" -I"E:\sprints workshop\Sprint6\delivery\3- SPI_Task1\MC2\LIBRARY" -I"E:\sprints workshop\Sprint6\delivery\3- SPI_Task1\MC2\MCAL\DIO" -I"E:\sprints workshop\Sprint6\delivery\3- SPI_Task1\MC2\MCAL\SPI" -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

