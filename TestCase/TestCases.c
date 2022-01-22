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
static uint16_t* ptr_null;
static uint8_t u8_ID;
static uint8_t u8_PassedCounter = 0;
static ADC_ERROR_state_t ADC_ErrorState;


/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
void CallBackFunc()
{


}

void TestBeforeInit(void)
{
	uint16_t u16_data;

	u8_ID = 1;
	ADC_ErrorState = ADC_Read(ADC_CH_0, &u16_data);
	if (ADC_ErrorState == E_ADC_NOT_INIT)
	{
		u8_PassedCounter++;
	}
	else
	{
		//misra rule
		//FAILED
	}

	u8_ID = 2;
	ADC_ErrorState = ADC_EnableInterrupt();
	if (ADC_ErrorState == E_ADC_NOT_INIT)
	{
		u8_PassedCounter++;
	}
	else
	{
		//misra rule
		//FAILED
	}

	u8_ID = 3;
	ADC_ErrorState = ADC_DisableInterrupt();
	if (ADC_ErrorState == E_ADC_NOT_INIT)
	{
		u8_PassedCounter++;
	}
	else
	{
		//misra rule
		//FAILED
	}

	u8_ID = 4;
	ADC_ErrorState = ADC_SetCallback(CallBackFunc);
	if (ADC_ErrorState == E_ADC_NOT_INIT)
	{
		u8_PassedCounter++;
	}
	else
	{
		//misra rule
		//FAILED
	}
}

void TestInit(void)
{
	/* initialize */
	u8_ID = 5;
	ADC_ErrorState = ADC_Init();
	if (
			(ADC_ErrorState == E_ADC_SUCCESS) && (ADMUX == ADC_REFERENCE_SELECTION) &&
			(ADCSRA == ADC_CONTROL_MASK)
	)
	{
		u8_PassedCounter++;
	}
	else
	{
		//misra rule
		//FAILED
	}

	/* initialize before */
	u8_ID = 6;
	ADC_ErrorState = ADC_Init();
	if (
			(ADC_ErrorState == E_ADC_INIT_BEFORE)
	)
	{
		u8_PassedCounter++;
	}
	else
	{
		//misra rule
		//FAILED
	}
}

void TestRead(void)
{
	uint16_t u16_data;

	/* Null Pointer */
	u8_ID = 7;
	ADC_ErrorState = ADC_Read(ADC_CH_0, ptr_null);
	if (
			(ADC_ErrorState == E_ADC_NULL_PTR)
	)
	{
		u8_PassedCounter++;
	}
	else
	{
		//misra rule
		//FAILED
	}

	/* Invalid Channel */
	u8_ID = 8;
	ADC_ErrorState = ADC_Read(INVALID_CHANNEL, &u16_data);
	if (
			(ADC_ErrorState == E_ADC_INVALID_CH)
	)
	{
		u8_PassedCounter++;
	}
	else
	{
		//misra rule
		//FAILED
	}

	/* Pre-set ADC readings data. */
	ADCL = 0xFF;
	ADCH = 0x03;

	/* Read */
	u8_ID = 9;
	ADC_ErrorState = ADC_Read(ADC_CH_0, &u16_data);
	if (
			(ADC_ErrorState == E_ADC_SUCCESS) && (u16_data == 0x3FF)
	)
	{
		u8_PassedCounter++;
	}
	else
	{
		//misra rule
		//FAILED
	}
}

void TestEnableInterrupt(void)
{
	/* Clear Interrupt Bit */
	ADCSRA &= ~(ADC_INTERRUPT_EN);

	u8_ID = 10;
	ADC_ErrorState = ADC_EnableInterrupt();
	if (
			(ADC_ErrorState == E_ADC_SUCCESS) && (ADCSRA & ADC_INTERRUPT_EN)
	)
	{
		u8_PassedCounter++;
	}
	else
	{
		//misra rule
		//FAILED
	}
}

void TestDisableInterrupt(void)
{
	/* Set Interrupt Bit */
	ADCSRA |= (ADC_INTERRUPT_EN);

	u8_ID = 11;
	ADC_ErrorState = ADC_DisableInterrupt();
	if (
			(ADC_ErrorState == E_ADC_SUCCESS) && !(ADCSRA & ADC_INTERRUPT_EN)
	)
	{
		u8_PassedCounter++;
	}
	else
	{
		//misra rule
		//FAILED
	}
}
