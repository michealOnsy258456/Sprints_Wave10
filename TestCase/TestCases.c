/*
 * TestCases.c
 *
 *  Created on: Jan 19, 2022
 *      Author: Micheal-Onsy
 */

/*- INCLUDES
 ----------------------------------------------*/
#include "TestCases.h"

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static uint8_t* ptr_null;
static uint8_t u8_ID;
static uint8_t u8_PassedCounter = 0;
static KEYPAD_ERROR_state_t KEYPAD_ErrorState;


/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/**
 * @brief: This function tests Get Keypad pressed value.
 */
void TestGetKeyValue(void)
{
	/* Null Pointer */
	u8_ID = 1;
	KEYPAD_ErrorState = KeyPad_getPressedKey( ptr_null);
	if (KEYPAD_ErrorState == E_KEYPAD_NULL_PTR)
	{
		u8_PassedCounter++;
	}
	else
	{
		/* Keypad test case failed*/
		/*Misra rule*/
	}

	uint8_t uint8_data;

	/* Valid data */
	u8_ID = 2;
	KEYPAD_ErrorState = KeyPad_getPressedKey( &uint8_data);
	if ( (KEYPAD_ErrorState == E_KEYPAD_SUCCESS) && (uint8_data == 0) )
	{
		u8_PassedCounter++;
	}
	else
	{
		/* Keypad test case failed*/
		/*Misra rule*/
	}
}

