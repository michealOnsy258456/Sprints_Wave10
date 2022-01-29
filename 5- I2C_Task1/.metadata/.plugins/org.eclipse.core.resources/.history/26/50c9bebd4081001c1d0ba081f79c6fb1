/*
 * APP.c
 *
 *  Created on: Jan 24, 2022
 *      Author: Micheal-Onsy
 */
#include "APP.h"

/*GLOBAL VARIABLE
----------------------------*/
uint8_t data=0;

void TWI_ISR(void);
void App_Init(void){

	TWI_Init();
	TWI_EnableInterrupt();
	TWI_SetCallback(&TWI_ISR);
	DIO_setPortDirection(PORTa,DIO_u8_OUTPUT);
	GI_EnableGI();
}
void App_Update(void){

}
void TWI_ISR(void)
{
	TWI_RecDataAck(&data);
	DIO_writePortValue(PORTa,data);

}
