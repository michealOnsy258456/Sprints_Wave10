/*
 * APP.c
 *
 *  Created on: Jan 24, 2022
 *      Author: Micheal-Onsy
 */
#include "APP.h"
/*GLOBAL STATIC VARIABLE
----------------------------*/
uint8_t gu8_ReceiverBuffer[20];


uint8_t AppInit(void)
{
	UART_Config config={UART_1StopBit,UART_8Bit,UART_AsyncDouble,UART_Disable};
	UART_VidInit(&config,9600); // initialize UART driver
	return 0;
}
uint8_t AppUpdate(void)
{
	UART_receiveString(gu8_ReceiverBuffer);
	UART_sendString(gu8_ReceiverBuffer);
	UART_sendByte('\r');
	return 0;
}
