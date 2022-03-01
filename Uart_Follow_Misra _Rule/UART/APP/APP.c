/******************************************************************************
 *
 * [MODULE]: APPLICATION
 *
 * [FILE NAME]: App.c
 *
 * [DESCRIPTION]: Source file for the Application
 *
 * [AUTHOR]: Micheal Onsy
 *
 *******************************************************************************/

/*******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/
#include "APP.h"
/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
uint8_t gu8_ReceiverBuffer[20];
/*******************************************************************************
 * [Function Name]: App_init
 *
 * [Description]: 	Function to Initialize the application
 *
 *******************************************************************************/

void APP_Init(void)
{
	UART_Config config={UART_1StopBit,UART_8Bit,UART_AsyncDouble,UART_Disable}; /* configuration of UART driver */
	UART_VidInit(&config,9600); /* initialize UART driver */
}

/*******************************************************************************
 * [Function Name]: App_Update
 *
 * [Description]: 	Function to update the state of the application
 *
 *******************************************************************************/
void APP_Update(void)
{
	UART_receiveString(gu8_ReceiverBuffer); /* Receive data from Uart */
	UART_sendString(gu8_ReceiverBuffer);    /* Sent data from Uart */
	UART_sendByte('\r');   				    /* sent newline */
}
