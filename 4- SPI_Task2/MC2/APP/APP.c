/*
 * APP.c
 *
 *  Created on: Jan 24, 2022
 *      Author: Micheal-Onsy
 */
#include "APP.h"


/*GLOBAL VARIABLE
----------------------------*/
uint8_t str[20];




void App_Init(void)
{
	UART_Config Config = {UART_1StopBit,UART_8Bit,UART_AsyncDouble,UART_Disable};
	UART_VidInit(&Config,9600);
	SPI_initSlave();
}
void APP_Update(void)
{
	SPI_ReceiveString(str);
	UART_sendString(str);
	UART_sendByte('\r');
}
