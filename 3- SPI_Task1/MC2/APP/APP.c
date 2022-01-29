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
uint8_t gu8_ReceiveData = 0;


/*******************************************************************************
 * [Function Name]: App_init
 *
 * [Description]: 	Function to Initialize the application
 *
 *******************************************************************************/

void APP_Init(void)
{
	SPI_initSlave();//Initialize the SPI As Slave
	gu8_ReceiveData=SPI_recieveByte();//Receive data from spi


	DIO_setPortDirection(PORTc,DIO_u8_OUTPUT);//Initialize this port Output
	DIO_writePortValue(PORTc,gu8_ReceiveData);//Write this port value

}