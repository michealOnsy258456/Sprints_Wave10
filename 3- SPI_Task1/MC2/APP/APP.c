/*
 * APP.c
 *
 *  Created on: Jan 24, 2022
 *      Author: Micheal-Onsy
 */
#include "APP.h"


/*GLOBAL VARIABLE
----------------------------*/
uint8_t gu8_ReceiveData = 0;


void AppInit(void)
{
	SPI_initSlave();
	gu8_ReceiveData=SPI_recieveByte();


	DIO_setPortDirection(PORTc,DIO_u8_OUTPUT);
	DIO_writePortValue(PORTc,gu8_ReceiveData);

}
