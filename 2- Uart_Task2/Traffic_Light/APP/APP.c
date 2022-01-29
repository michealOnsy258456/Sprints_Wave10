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
#include <avr/delay.h>

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
uint8_t gu8_ReceiverBuffer[6]		={0};
uint8_t Counter						= 0;
uint8_t State 						= 0;



/*******************************************************************************
 * [Function Name]: App_init
 *
 * [Description]: 	Function to Initialize the application
 *
 *******************************************************************************/
void APP_Init(void)
{
	UART_Config config={UART_1StopBit,UART_8Bit,UART_AsyncDouble,UART_Disable};// configuration of UART driver
	UART_VidInit(&config,9600); // initialize UART driver
	LED_Init(LED0);// initialize LED0
	LED_Init(LED1);// initialize LED1
	LED_Init(LED2);// initialize LED2

}

/*******************************************************************************
 * [Function Name]: App_Update
 *
 * [Description]: 	Function to update the state of the application
 *
 *******************************************************************************/
void APP_Update(void)
{
	UART_receiveString(gu8_ReceiverBuffer);//Receive data from Uart

	/*Compare Received Data  */
	if (strcmp(gu8_ReceiverBuffer,"START")==0)
	{
		State=GREEN;//Put On This Variable to indicate To  Open led green
	}
	if (strcmp(gu8_ReceiverBuffer,"STOP")==0)
	{
		State=RED;//Put On This Variable to indicate To  Open led red
	}

	if (strcmp(gu8_ReceiverBuffer,"WAIT")==0)
	{
		State=YELLOW;//Put On This Variable to indicate To  Open led yellow
	}
	if (strcmp(gu8_ReceiverBuffer,"AT")==0)
	{
		State=AT;//Put On This Variable to indicate To  close All led
	}

	switch (State)
	{
	case GREEN:
		LED_AllClose();//close all led at first
		LED_Open(LED0);//open LED0
		UART_sendString("Green LED is on"); //to send this word to the terminal
		UART_sendByte(NEW_LINE);//to send NewLINE to the terminal
		State = 0;//make this variable zero to receive new data on it
		break;
	case YELLOW:
		LED_AllClose();//close all led at first
		LED_Open(LED1);//open LED0
		UART_sendString("Yellow LED is on");//to send this word to the terminal
		UART_sendByte(NEW_LINE);//to send NewLINE to the terminal
		State = 0 ;//make this variable zero to receive new data on it
		break;
	case RED:
		LED_AllClose();//close all led at first
		LED_Open(LED2);//open LED0
		UART_sendString("Red LED is on");//to send this word to the terminal
		UART_sendByte(NEW_LINE);//to send NewLINE to the terminal
		State = 0;//make this variable zero to receive new data on it
		break;
	case AT:
		LED_AllClose();//close all led at first
		UART_sendString("OK");
		UART_sendByte(NEW_LINE);//to send NewLINE to the terminal
		State = 0;//make this variable zero to receive new data on it
		break;
	default:
		UART_sendString("Error");/* Error Message */
		UART_sendByte(NEW_LINE);//to send NewLINE to the terminal
		State = 0;//make this variable zero to receive new data on it
		break;
	}
	APP_ClearBuffer();//to clear this variable to receive new data on it

}


/*******************************************************************************
 * [Function Name]: APP_ClearBuffer
 *
 * [Description]: 	Function to Clear Data From array
 *
 *******************************************************************************/
void APP_ClearBuffer(void)
{
	for(Counter = 0 ;Counter<6  ; Counter++)
	{
		gu8_ReceiverBuffer[Counter] = 0;
	}

}
