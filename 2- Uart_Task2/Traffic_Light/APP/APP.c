/*
 * APP.c
 *
 *  Created on: Jan 24, 2022
 *      Author: Micheal-Onsy
 */
#include "APP.h"

#include <avr/delay.h>

/*GLOBAL VARIABLE
----------------------------*/
uint8_t gu8_ReceiverBuffer[6]		={0};
uint8_t Counter						= 0;
uint8_t State 						= 0;




void AppInit(void)
{
	UART_Config config={UART_1StopBit,UART_8Bit,UART_AsyncDouble,UART_Disable};
	UART_VidInit(&config,9600); // initialize UART driver
	LED_Init(LED0);
	LED_Init(LED1);
	LED_Init(LED2);

}
void AppUpdate(void)
{
	UART_receiveString(gu8_ReceiverBuffer);

	if (strcmp(gu8_ReceiverBuffer,"START")==0)
	{
		State=GREEN;
	}
	if (strcmp(gu8_ReceiverBuffer,"STOP")==0)
	{
		State=RED;
	}

	if (strcmp(gu8_ReceiverBuffer,"WAIT")==0)
	{
		State=YELLOW;
	}
	if (strcmp(gu8_ReceiverBuffer,"AT")==0)
	{
		State=AT;
	}

	switch (State)
	{
	case GREEN:
		LED_AllClose();
		LED_Open(LED0);
		UART_sendString("Green LED is on");
		UART_sendByte(NEW_LINE);
		State = 0;
		break;
	case YELLOW:
		LED_AllClose();
		LED_Open(LED1);
		UART_sendString("Yellow LED is on");
		UART_sendByte(NEW_LINE);
		State = 0 ;
		break;
	case RED:
		LED_AllClose();
		LED_Open(LED2);
		UART_sendString("Red LED is on");
		UART_sendByte(NEW_LINE);
		State = 0;
		break;
	case AT:
		LED_AllClose();
		UART_sendString("OK");
		UART_sendByte(NEW_LINE);
		State = 0;
		break;
	default:
		UART_sendString("Error");
		UART_sendByte(NEW_LINE);
		State = 0;
		break;
	}
	APP_ClearBuffer();

}


void APP_ClearBuffer(void)
{
	for(Counter = 0 ;Counter<6  ; Counter++)
	{
		gu8_ReceiverBuffer[Counter] = 0;
	}

}