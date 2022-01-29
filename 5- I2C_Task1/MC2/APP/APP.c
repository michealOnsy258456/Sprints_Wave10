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
uint8_t data='A';
/*******************************************************************************
 * [Function Name]: App_init
 *
 * [Description]: 	Function to Initialize the application
 *
 *******************************************************************************/
void APP_Init(void){

	TWI_Init();//Initialization I2C
	TWI_EnableInterrupt();//Initialization Interrupt
	TWI_SetCallback(&TWI_ISR);//Function To Call Another Function To Put it in ISR
	DIO_setPortDirection(PORTa,DIO_u8_OUTPUT);//Set the Direction of portA Output Port
	GI_EnableGI();//to enable Interrupt
}
/*******************************************************************************
 * [Function Name]: App_Update
 *
 * [Description]: 	Function to update the state of the application
 *
 *******************************************************************************/
void APP_Update(void){

}
/*******************************************************************************
 * [Function Name]: TWI_ISR
 *
 * [Description]: 	Function it call when interrupt happened in application
 *
 *******************************************************************************/
void TWI_ISR(void)
{
	TWI_RecDataAck(&data);//Receive Data From The MC By I2C
	DIO_writePortValue(PORTa,data);//Set the Value of portA

}
