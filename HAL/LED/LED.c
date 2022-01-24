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
	case LED0:
		DIO_setPinDirection(LED_PORT, LED_PIN4, DIO_u8_OUTPUT);
		break;
	case LED1:
		DIO_setPinDirection(LED_PORT, LED_PIN5, DIO_u8_OUTPUT);
		break;
	case LED2:
		DIO_setPinDirection(LED_PORT, LED_PIN6, DIO_u8_OUTPUT);
		break;
	case LED3:
		DIO_setPinDirection(LED_PORT, LED_PIN7, DIO_u8_OUTPUT);
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
	case LED0:
		DIO_TogglePin(LED_PORT, LED_PIN4);
		break;
	case LED1:
		DIO_TogglePin(LED_PORT, LED_PIN5);
		break;
	case LED2:
		DIO_TogglePin(LED_PORT, LED_PIN6);
		break;
	case LED3:
		DIO_TogglePin(LED_PORT, LED_PIN7);
		break;
	default:
		u8_ERROR_STAT = ERROR_NOK;
		break;
	}
	return u8_ERROR_STAT;
}
ERROR_STATE_t LED_Open(uint8_t LED_ID)
{
	ERROR_STATE_t u8_ERROR_STAT = ERROR_OK;
	switch(LED_ID)
	{
	case LED0:
		SET_BIT(PORTB, LED_PIN4);
		break;
	case LED1:
		SET_BIT(PORTB, LED_PIN5);
		break;
	case LED2:
		SET_BIT(PORTB, LED_PIN6);
		break;
	case LED3:
		SET_BIT(PORTB, LED_PIN7);
		break;
	default:
		u8_ERROR_STAT = ERROR_NOK;
		break;
	}
	return u8_ERROR_STAT;
}
ERROR_STATE_t LED_Close(uint8_t LED_ID)
{
	ERROR_STATE_t u8_ERROR_STAT = ERROR_OK;
	switch(LED_ID)
	{
	case LED0:
		CLEAR_BIT(PORTB, LED_PIN4);
		break;
	case LED1:
		CLEAR_BIT(PORTB, LED_PIN5);
		break;
	case LED2:
		CLEAR_BIT(PORTB, LED_PIN6);
		break;
	case LED3:
		CLEAR_BIT(PORTB, LED_PIN7);
		break;
	default:
		u8_ERROR_STAT = ERROR_NOK;
		break;
	}
	return u8_ERROR_STAT;
}

ERROR_STATE_t LED_AllOpen()
{
	ERROR_STATE_t u8_ERROR_STAT = ERROR_OK;

	SET_BIT(PORTB,LED_PIN4);
	SET_BIT(PORTB,LED_PIN5);
	SET_BIT(PORTB,LED_PIN6);
	SET_BIT(PORTB,LED_PIN7);

	return u8_ERROR_STAT;
}
ERROR_STATE_t LED_AllClose()
{
	ERROR_STATE_t u8_ERROR_STAT = ERROR_OK;

	CLEAR_BIT(PORTB,LED_PIN4);
	CLEAR_BIT(PORTB,LED_PIN5);
	CLEAR_BIT(PORTB,LED_PIN6);
	CLEAR_BIT(PORTB,LED_PIN7);

	return u8_ERROR_STAT;
}

