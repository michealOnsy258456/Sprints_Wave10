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
uint8_t str[20];

/*******************************************************************************
 * [Function Name]: App_init
 *
 * [Description]: 	Function to Initialize the application
 *
 *******************************************************************************/
void APP_Init(void)
{
	UART_Config Config = {UART_1StopBit,UART_8Bit,UART_AsyncDouble,UART_Disable};//configuration of uart
	UART_VidInit(&Config,9600);//Inilialization uart
	SPI_initMaster(); /* Master Initialization */
}
void APP_Update(void)
{
	UART_receiveString(str);//Receive data from Uart
	_delay_ms(100); /* delay until MC2 finish its initialization task */
	SPI_sendString(str);//Send data To anothor MC

}
