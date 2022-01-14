/*
 * LED.c
 *
 *  Created on: Jan 3, 2022
 *      Author: Micheal-Onsy
 */


#include "LED.h"
/*- APIs IMPLEMENTATION
-----------------------------------*/
ERROR_STATE_t LED_Init(uint8_t LED_ID)
{
	ERROR_STATE_t u8_ERROR_STAT = ERROR_OK;
	switch(LED_ID)
	{
	case LED1:
		DIO_setPinDirection(LED_PORT, LED_PIN1, DIO_u8_OUTPUT);
		break;
	case LED2:
		DIO_setPinDirection(LED_PORT, LED_PIN6, DIO_u8_OUTPUT);
		break;
	case LED3:
		DIO_setPinDirection(LED_PORT, LED_PIN3, DIO_u8_OUTPUT);
		break;
	default:
		u8_ERROR_STAT = ERROR_NOK;
		break;
	}
	return u8_ERROR_STAT;
}
ERROR_STATE_t LED_toggle(uint8_t LED_ID)
{
	ERROR_STATE_t u8_ERROR_STAT = ERROR_OK;
	switch(LED_ID)
	{
	case LED1:
		DIO_TogglePin(LED_PORT, LED_PIN1);
		break;
	case LED2:
		DIO_TogglePin(LED_PORT, LED_PIN6);
		break;
	case LED3:
		DIO_TogglePin(LED_PORT, LED_PIN3);
		break;
	default:
		u8_ERROR_STAT = ERROR_NOK;
		break;
	}
	return u8_ERROR_STAT;
}
