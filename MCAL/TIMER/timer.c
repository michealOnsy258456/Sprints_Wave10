/************************************************************************************
 *
 * [MODULE]: TIMER
 *
 * [FILE NAME]: timer.c
 *
 * [DESCRIPTION]: Source file for the TIMER AVR driver
 *
 * [AUTHOR]: Ahmed Hassan
 *
 ************************************************************************************/

#include "timer.h"

static volatile void (*g_callBackPtrTimer0)(void) = NULL_PTR;
static volatile void (*g_callBackPtrTimer1)(void) = NULL_PTR;
static volatile void (*g_callBackPtrTimer2)(void) = NULL_PTR;

ISR(TIMER0_OVF_vect)
{
	/* Check if Pointer is not a NULL one, to avoid Segmentation fault */
	if(g_callBackPtrTimer0 != NULL_PTR)
	{
		/*
		 * Call the callback function in the application after the overflow has
		 * occurred in TIMER0 (NORMAL MODE)
		 */
		(*g_callBackPtrTimer0)();
	}
}

ISR(TIMER0_COMP_vect)
{
	/* Check if Pointer is not a NULL one, to avoid Segmentation fault */
	if(g_callBackPtrTimer0 != NULL_PTR)
	{
		/*
		 * Call the callback function in the application after the compare match has
		 * occurred in TIMER0 (COMPARE MODE)
		 */
		(*g_callBackPtrTimer0)();
	}
}

ISR(TIMER1_OVF_vect)
{
	/* Check if Pointer is not a NULL one, to avoid Segmentation fault */
	if(g_callBackPtrTimer1 != NULL_PTR)
	{
		/*
		 * Call the callback function in the application after the overflow has
		 * occurred in TIMER1 (NORMAL MODE)
		 */
		(*g_callBackPtrTimer1)();
	}
}

ISR(TIMER1_COMPA_vect)
{
	/* Check if Pointer is not a NULL one, to avoid Segmentation fault */
	if(g_callBackPtrTimer1 != NULL_PTR)
	{
		/*
		 * Call the callback function in the application after the compare match has
		 * occurred in TIMER1 Channel A (COMPARE MODE)
		 */
		(*g_callBackPtrTimer1)();
	}
}


ISR(TIMER2_OVF_vect)
{
	/* Check if Pointer is not a NULL one, to avoid Segmentation fault */
	if(g_callBackPtrTimer2 != NULL_PTR)
	{
		/*
		 * Call the callback function in the application after the overflow has
		 * occurred in TIMER2 (NORMAL MODE)
		 */
		(*g_callBackPtrTimer2)();
	}
}

ISR(TIMER2_COMP_vect)
{
	/* Check if Pointer is not a NULL one, to avoid Segmentation fault */
	if(g_callBackPtrTimer2 != NULL_PTR)
	{
		/*
		 * Call the callback function in the application after the compare match has
		 * occurred in TIMER2 (COMPARE MODE)
		 */
		(*g_callBackPtrTimer2)();
	}
}

enuTIMER_E_STATE_t TIMER_init(const strTIMER_ConfigType_t * Config_Ptr)
{
	enuTIMER_E_STATE_t enu_ErrorState = E_NOT_OK;

	switch(Config_Ptr -> timer_ID)
	{

	case TIMER_0:

		TCNT0_R = 0x00;
		TCCR0_R = 0x00;
		OCR0_R  = 0x00;

		TCNT0_R = ( (Config_Ptr -> intialValue) & 0xFF);

		switch(Config_Ptr -> timer_Mode)
		{

		case NORMAL:

			TCCR0_R  = (1 << FOC0_BIT);
			TIMSK_R |= (1 << TOIE0_BIT);
			enu_ErrorState = TIMER_E_PARAM_VALID;
			break;

		case COMPARE:

			OCR0_R   = ( (Config_Ptr -> compareValue) & 0xFF);
			TCCR0_R  = (1 << FOC0_BIT) | (1 << WGM01_BIT);
			TIMSK_R |= (1 << OCIE0_BIT);
			enu_ErrorState = TIMER_E_PARAM_VALID;
			break;

		default:

			enu_ErrorState = TIMER_E_PARAM_INVALID_MODE;
			break;

		}	/* END CASE OF TIMER0 */
		break;

	case TIMER_1:

		TCNT1_R  = 0x0000;
		OCR1A_R  = 0x0000;
		TCCR1A_R = 0x00;
		TCCR1B_R = 0x00;

		TCNT1_R = ( (Config_Ptr -> intialValue) & 0xFFFF);

		switch(Config_Ptr -> timer_Mode)
		{

		case NORMAL:

			TCCR1A_R = (1 << FOC1A_BIT)  | (1 << FOC1B_BIT);
			TIMSK_R |= (1 << TOIE1_BIT);
			enu_ErrorState = TIMER_E_PARAM_VALID;
			break;

		case COMPARE:

			OCR1A_R   = ( (Config_Ptr -> compareValue) & 0xFFFF);
			TCCR1A_R  = (1 << FOC1A_BIT) | (1 << FOC1B_BIT);
			TCCR1B_R |= (1 << WGM12_BIT);
			TIMSK_R  |= (1 << OCIE1A_BIT);
			enu_ErrorState = TIMER_E_PARAM_VALID;
			break;

		default:
			enu_ErrorState = TIMER_E_PARAM_INVALID_MODE;
			break;

		}	/* END CASE OF TIMER1 */
		break;

	case TIMER_2:

		TCNT2_R = 0x00;
		TCCR2_R = 0x00;
		OCR2_R  = 0x00;

		TCNT2_R = ( (Config_Ptr -> intialValue) & 0xFF);

		switch(Config_Ptr -> timer_Mode)
		{

		case NORMAL:

			TCCR2_R  = (1 << FOC2_BIT);
			TIMSK_R |= (1 << TOIE2_BIT);
			enu_ErrorState = TIMER_E_PARAM_VALID;
			break;

		case COMPARE:

			OCR2_R   = ( (Config_Ptr -> compareValue) & 0xFF);
			TCCR2_R  = (1 << FOC2_BIT) | (1 << WGM21_BIT);
			TIMSK_R |= (1 << OCIE2_BIT);
			enu_ErrorState = TIMER_E_PARAM_VALID;
			break;

		default:

			enu_ErrorState = TIMER_E_PARAM_INVALID_MODE;
			break;
		}	/* END CASE OF TIMER2 */
		break;

	default:
		enu_ErrorState = TIMER_E_PARAM_INVALID_ID;	/* Invalid timer id */
		break;
	}
	return enu_ErrorState;
}


enuTIMER_E_STATE_t TIMER_setCallBack(void(*a_ptr)(void), const enuTIMER_ID_t enu_timerID)
{
	enuTIMER_E_STATE_t enu_ErrorState = E_NOT_OK;

	if(a_ptr == NULL_PTR)
	{
		enu_ErrorState = TIMER_E_PARAM_POINTER;	/* Invalid pointer "NULL" */
	}
	else
	{
		switch(enu_timerID)
		{

		case TIMER_0:

			/* Save the address of the Call back function of TIMER0 in a global variable */
			g_callBackPtrTimer0 = a_ptr;
			enu_ErrorState = TIMER_E_PARAM_VALID;
			break;

		case TIMER_1:

			/* Save the address of the Call back function of TIMER1 in a global variable */
			g_callBackPtrTimer1 = a_ptr;
			enu_ErrorState = TIMER_E_PARAM_VALID;
			break;

		case TIMER_2:

			/* Save the address of the Call back function of TIMER2 in a global variable */
			g_callBackPtrTimer2 = a_ptr;
			enu_ErrorState = TIMER_E_PARAM_VALID;
			break;

		default:
			break;
			enu_ErrorState = TIMER_E_PARAM_INVALID_ID;	/* Invalid timer id */
		}
	}
	return enu_ErrorState;
}

/******************************************************************************
 * [Function Name]: TIMER_start
 *
 * [Description]: 	Function to enable the timer Driver
 *
 * [Args]:			enu_timerID, enu_timerClock
 *
 * [in]			  	enu_timerID: Enumerator to TIMER ID
 * 					enu_timerClock: Enumerator to TIMER CLOCK
 *
 * [out]		  	None
 *
 * [in/out]		 	None
 *
 * [Returns]:       Error state
 ******************************************************************************/
enuTIMER_E_STATE_t TIMER_start(const enuTIMER_ID_t enu_timerID, const enuTIMER_Clock_t enu_timerClock)
{
	enuTIMER_E_STATE_t enu_ErrorState = E_NOT_OK;

	switch(enu_timerID)
	{

	 /* Insert the required Clock in the First three bits (CS02, CS01, CS00) in TCCR0 register */
	case TIMER_0:
		TCCR0_R  = (TCCR0_R & 0xF8) | (enu_timerClock);
		enu_ErrorState = TIMER_E_PARAM_VALID;	/* Update the error state with no error */
		break;

	/* Insert the required Clock in the First three bits (CS12, CS11, CS10) in TCCR1B register */
	case TIMER_1:
		TCCR1B_R  = (TCCR1B_R & 0xF8) | (enu_timerClock);
		enu_ErrorState = TIMER_E_PARAM_VALID;	/* Update the error state with no error */
		break;

	/* Insert the required Clock in the First three bits (CS22, CS21, CS20) in TCCR2 register */
	case TIMER_2:
		TCCR2_R  = (TCCR2_R & 0xF8) | (enu_timerClock);
		enu_ErrorState = TIMER_E_PARAM_VALID;	/* Update the error state with no error */
		break;

	default:
		enu_ErrorState = TIMER_E_PARAM_INVALID_ID;	/* Invalid timer id */
		break;
	}
	return enu_ErrorState;
}

/******************************************************************************
 * [Function Name]: TIMER_stop
 *
 * [Description]:   Function to stop the TIMER from counting
 *
 * [Args]:			enu_timerID
 *
 * [in]				enu_timerID: Enumerator to TIMER ID
 *
 * [out]		  	None
 *
 * [in/out]		 	None
 *
 * [Returns]:       Error state
 ******************************************************************************/
enuTIMER_E_STATE_t TIMER_stop(const enuTIMER_ID_t enu_timerID)
{
	enuTIMER_E_STATE_t enu_ErrorState = E_NOT_OK;

	switch(enu_timerID)
	{

	case TIMER_0:

		TCCR0_R  = (TCCR0_R & 0xF8);	/* Clear Clock bits in TIMER0 */
		enu_ErrorState = TIMER_E_PARAM_VALID;	/* Update the error state with no error */
		break;

	case TIMER_1:

		TCCR1B_R = (TCCR1B_R & 0xF8);	/* Clear Clock bits in TIMER1 */
		enu_ErrorState = TIMER_E_PARAM_VALID;	/* Update the error state with no error */
		break;

	case TIMER_2:

		TCCR2_R  = (TCCR2_R & 0xF8);	/* Clear Clock bits in TIMER2 */
		enu_ErrorState = TIMER_E_PARAM_VALID;	/* Update the error state with no error */
		break;

	default:
		enu_ErrorState = TIMER_E_PARAM_INVALID_ID;	/* Invalid timer id */
		break;
	}
	return enu_ErrorState;
}

/******************************************************************************
 * [Function Name]: TIMER_DeInit
 *
 * [Description]: 	Function to disable the TIMER Driver
 *
 * [Args]:			enu_timerID
 *
 * [in]				enu_timerID: Enumerator to TIMER ID
 *
 * [out]		  	None
 *
 * [in/out]		 	None
 *
 * [Returns]:       Error state
 ******************************************************************************/
enuTIMER_E_STATE_t TIMER_DeInit(const enuTIMER_ID_t enu_timerID)
{
	enuTIMER_E_STATE_t enu_ErrorState = E_NOT_OK;

	switch(enu_timerID)
	{

	case TIMER_0:

		/* Clear All TIMER0 Register */
		TCNT0_R = 0x00;
		TCCR0_R = 0x00;
		OCR0_R  = 0x00;

		/* Disable TIMER0 Interrupt Enable */
		TIMSK_R &= ~(1 << TOIE0_BIT) & ~(1 << OCIE0_BIT);

		/* Disable TIMER0 Interrupt Flag, by writing a logic one */
		TIFR_R |= (1 << OCF0_BIT) | (1 << TOV0_BIT);

		/* Update the error state with no error */
		enu_ErrorState = TIMER_E_PARAM_VALID;
		break;

	case TIMER_1:

		/* Clear All TIMER1 Register */
		TCNT1_R  = 0x0000;
		OCR1A_R  = 0x0000;
		TCCR1A_R = 0x00;
		TCCR1B_R = 0x00;

		/* Disable TIMER1 Interrupt Enable */
		TIMSK_R &= ~(1 << TOIE1_BIT) & ~(1 << OCIE1A_BIT);

		/* Disable TIMER1 Interrupt Flag, by writing a logic one */
		TIFR_R |= (1 << OCF1A_BIT) | (1 << OCF1B_BIT) | (1 << TOV1_BIT);

		/* Update the error state with no error */
		enu_ErrorState = TIMER_E_PARAM_VALID;
		break;

	case TIMER_2:

		/* Clear All TIMER2 Register */
		TCNT2_R = 0x00;
		TCCR2_R = 0x00;
		OCR2_R  = 0x00;

		/* Disable TIMER2 Interrupt Flags */
		TIMSK_R &= ~(1 << TOIE2_BIT) & ~(1 << OCIE2_BIT);

		/* Disable TIMER2 Interrupt Flag, by writing a logic one */
		TIFR_R |= (1 << OCF2_BIT) | (1 << TOV2_BIT);

		/* Update the error state with no error */
		enu_ErrorState = TIMER_E_PARAM_VALID;
		break;

	default:

		/* Update the error state with error */
		enu_ErrorState = TIMER_E_PARAM_INVALID_ID;
		break;
	}
	return enu_ErrorState;
}
