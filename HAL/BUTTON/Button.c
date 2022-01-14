/*
 * Button.c
 *
 *  Created on: Jan 3, 2022
 *      Author: Micheal-Onsy
 */


#include "Button.h"
/*- APIs IMPLEMENTATION----------------------------------------------*/
ERROR_STATE_t Button_Init(uint8_t Button_ID)
{
	ERROR_STATE_t u8_ERROR_STAT = ERROR_OK;
	switch(Button_ID)
	{
	case BUTTON1:
		DIO_setPinDirection(BUTTON_PORT, BUTTON_PIN2, DIO_u8_INPUT);
		DIO_SetPullupRes(BUTTON_PORT, BUTTON_PIN2);
		break;
	case BUTTON2:
		DIO_setPinDirection(BUTTON_PORT, BUTTON_PIN2, DIO_u8_INPUT);
		DIO_SetPullupRes(BUTTON_PORT, BUTTON_PIN2);
		break;
	case BUTTON3:
		DIO_setPinDirection(BUTTON_PORT, BUTTON_PIN3, DIO_u8_INPUT);
		DIO_SetPullupRes(BUTTON_PORT, BUTTON_PIN3);
		break;
	default:
		u8_ERROR_STAT = ERROR_NOK;
		break;
	}
	return u8_ERROR_STAT;
}
ERROR_STATE_t Button_getState(uint8_t Button_ID,uint8_t * State)
{
	ERROR_STATE_t u8_ERROR_STAT = ERROR_OK;
	uint8_t u8_currentValue = 0;
	uint8_t u8_oldValue = 0;
	volatile uint8_t u8_counter = 0;
	if(NULL_PTR==State)
	{
		u8_ERROR_STAT = ERROR_NOK;
	}
	else
	{
		/*Debounce handling*/
		/*how i make her */

		switch(Button_ID)
		{
		case BUTTON1:
			for(u8_counter=0;u8_counter<10;u8_counter++)
			{
				DIO_readPin(BUTTON_PORT, BUTTON_PIN2, &u8_currentValue);
				if (u8_currentValue == u8_oldValue)
				{
					u8_counter++;
				}
				else
				{
					u8_counter = 0;
				}
				u8_oldValue = u8_currentValue;
			}
			break;
		case BUTTON2:
			for(u8_counter=0;u8_counter<10;u8_counter++)
			{
				DIO_readPin(BUTTON_PORT, BUTTON_PIN2, &u8_currentValue);
				if (u8_currentValue == u8_oldValue)
				{
					u8_counter++;
				}
				else
				{
					u8_counter = 0;
				}
				u8_oldValue = u8_currentValue;
			}
			break;

		case BUTTON3:
			for(u8_counter=0;u8_counter<10;u8_counter++)
			{
				DIO_readPin(BUTTON_PORT, BUTTON_PIN1, &u8_currentValue);
				if (u8_currentValue == u8_oldValue)
				{
					u8_counter++;
				}
				else
				{
					u8_counter = 0;
				}
				u8_oldValue = u8_currentValue;
			}
			break;

		default:
			u8_ERROR_STAT = ERROR_NOK;
			break;
		}
	}
	*State=u8_currentValue;
	return u8_ERROR_STAT;
}
