/*
 * APP.c
 *
 *  Created on: Jan 24, 2022
 *      Author: Micheal-Onsy
 */
#include "APP.h"


/*GLOBAL VARIABLE
----------------------------*/
uint8_t  gu8_SendData = 'A';


void AppInit(void)
{
	SPI_initMaster();
	_delay_ms(100); /* delay until MC2 finish its initialization task */
	SPI_sendByte(gu8_SendData);
}
