/*
 * TestCases.c
 *
 *  Created on: Jan 19, 2022
 *      Author: Micheal-Onsy
 */

/*- INCLUDES
 ----------------------------------------------*/
#include "TestCases.h"

static uint8_t uint8_ID;
static uint8_t u8_PassedCounter = 0;
static LCD_ERROR_state_t LCD_ErrorState;

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
void TestInit(void)
{
	/* Valid Channel */
	uint8_ID = 1;
	LCD_ErrorState = LCD_init();
	if (
			(LCD_ErrorState == E_LCD_SUCCESS)
	)
	{
		u8_PassedCounter++;
	}
	else
	{
		/*Print Test case Failed*/
		/*Misra Rule*/
	}
}



/**
 * @brief: This function tests Sending a Command to LCD.
 */
void TestSendCmd(void)
{
	/* Valid Channel */
	uint8_ID = 2;
	LCD_ErrorState = LCD_sendCommand(CLEAR_COMMAND);
	if (
			(LCD_ErrorState == E_LCD_SUCCESS)
	)
	{
		u8_PassedCounter++;
	}
	else
	{
		/*Print Test case Failed*/
		/*Misra Rule*/
	}
}

/**
 * @brief: This function tests Sending a char to LCD.
 */
void TestSendChar(void)
{


	/* Valid Channel */
	uint8_ID = 3;
	LCD_ErrorState = LCD_displayCharacter( 'a');
	if (
			(LCD_ErrorState == E_LCD_SUCCESS)
	)
	{
		u8_PassedCounter++;
	}
	else
	{
		/*Print Test case Failed*/
		/*Misra Rule*/
	}
}

/**
 * @brief: This function tests Sending a String to LCD.
 */
void TestSendString(void)
{
	/* Null Pointer */
	uint8_ID = 4;
	LCD_ErrorState = LCD_displayString(NULL_PTR);
	if(LCD_ErrorState == E_LCD_NULL_PTR)
	{
		u8_PassedCounter++;
	}
	else
	{
		/*Print Test case Failed*/
		/*Misra Rule*/
	}

	uint8_t String[3] = { 'a', 'b', '\0' };

	/* Valid Channel */
	uint8_ID =5;
	LCD_ErrorState = LCD_displayString(String);
	if (LCD_ErrorState == E_LCD_SUCCESS)
	{
		u8_PassedCounter++;
	}
	else
	{
		/*Print Test case Failed*/
		/*Misra Rule*/
	}
}
