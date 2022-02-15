/*
 * Robot.c
 *
 * Created: 2/12/2022 7:50:21 AM
 * Author : Ahmed_Ayman
 */ 

#include <avr/io.h>
#include "APP.h"
extern uint16_t Distance ; 
extern Ultrasonic_GPIOPINS_t  Ultrasonic_PINS ; 

int main(void)
{
	APP_Init();
    /* Replace with your application code */
    while (1) 
    {
		APP_UPdate();
    }
}

