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
uint8_t  gu8_SendData = 'A';



/*******************************************************************************
 * [Function Name]: App_init
 *
 * [Description]: 	Function to Initialize the application
 *
 *******************************************************************************/
void APP_Init(void)
{
	SPI_initMaster();// Initialize SPI driver
	_delay_ms(100); /* delay until MC2 finish its initialization task */
	SPI_sendByte(gu8_SendData);// Send to another MC this data
}
