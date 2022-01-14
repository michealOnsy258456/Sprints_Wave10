/*
 * Timer1.c
 *
 *  Created on: Jan 15, 2020
 *      Author: micheal_onsy
 */

#include "Timer.h"



/*- Global Variables
-----------------------------------*/

static volatile void (*g_callBackPtrTimer0)(void) = NULL_PTR;
static volatile void (*g_callBackPtrTimer2)(void) = NULL_PTR;
static volatile void (*g_callBackPtrTimer1)(void) = NULL_PTR;



/*- Interrupt Service Routines
-----------------------------------*/

/*-   TIMER0
-----------------------------------*/

ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtrTimer0 != NULL_PTR)
	{
		(*g_callBackPtrTimer0)();
	}
}

ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtrTimer0 != NULL_PTR)
	{

		(*g_callBackPtrTimer0)();
	}
}

/*-   TIMER1
-----------------------------------*/
ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtrTimer1 != NULL_PTR)
	{
		(*g_callBackPtrTimer1)();
	}
}

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtrTimer1 != NULL_PTR)
	{
		(*g_callBackPtrTimer1)();
	}
}

/*-   TIMER2
-----------------------------------*/

ISR(TIMER2_OVF_vect)
{
	if(g_callBackPtrTimer2 != NULL_PTR)
	{
		(*g_callBackPtrTimer2)();
	}
}

ISR(TIMER2_COMP_vect)
{
	if(g_callBackPtrTimer2 != NULL_PTR)
	{
		(*g_callBackPtrTimer2)();
	}
}

/************************************************************************************
 *                              Functions Definitions                               *
 ************************************************************************************/

void TIMER_VidInit(const TIM_Config * a_Ptr,uint16_t a_SetInitialValue,uint16_t a_SetCompare)
{

	switch(a_Ptr -> timer_ID)
	{

	case TIMER_0:
		TCNT0 = 0x00;
		OCR0  = 0x00;
		TCNT0 = a_SetInitialValue;

		if((a_Ptr -> timer_Mode)==NORMAL)
		{
			TCCR0  = (1 << FOC0);
			TIMSK |= (1 << TOIE0);
		}
		else if((a_Ptr -> timer_Mode)==COMPARE)
		{
			OCR0   = a_SetCompare;
			TCCR0  = (1 << FOC0) | (1 << WGM01);
			TIMSK |= (1 << OCIE0);
		}
		break;

	case TIMER_1:
		if((a_Ptr -> timer_Mode)==NORMAL)
		{
			TCNT1=a_SetInitialValue;
			TCCR1A=(1<<FOC1A)|(1<<FOC1B);
			TIMSK=(1<<TOIE1);
		}
		else if((a_Ptr -> timer_Mode)==COMPARE)
		{
			OCR1A=a_SetCompare;
			TCCR1A  = (1 << FOC1A) | (1 << FOC1B);
			TCCR1B |= (1 << WGM12);
			TIMSK  |= (1 << OCIE1A);
		}
		break;
	case TIMER_2:

		/*
		 * Clear All timer register before doing any operation,
		 * to ensure that timer will work correctly
		 */
		TCNT2 = a_SetInitialValue;
		if((a_Ptr -> timer_Mode)==NORMAL)
		{
			TCCR2  = (1 << FOC2);
			TIMSK |= (1 << TOIE2);
		}
		else if((a_Ptr -> timer_Mode)==COMPARE)
		{
			OCR2   = a_SetCompare;
			TCCR2  = (1 << FOC2) | (1 << WGM21);
			TIMSK |= (1 << OCIE2);

		}	/* END CASE OF TIMER2 */
		break;
	}
}
void TIMER_setCallBack(void(*a_ptr)(void), const TIM_ID a_timerID)
{
	switch(a_timerID)
	{
	case TIMER_0:
		g_callBackPtrTimer0 = a_ptr;
		break;
	case TIMER_1:
		g_callBackPtrTimer1 = a_ptr;
		break;
	case TIMER_2:
		g_callBackPtrTimer2 = a_ptr;
		break;
	}
}


void TIMER_Stop(const TIM_ID a_timerID)
{

	switch(a_timerID)
	{

	case TIMER_0:
		TCCR0  = ( TCCR0 & 0xF8 );
		break;
	case TIMER_1:
		TCCR1B = (TCCR1B & 0xF8);
		break;
	case TIMER_2:
		TCCR2  = ( TCCR2 & 0xF8 );
		break;
	}
}

void TIMER_Start(const TIM_Config * a_Ptr)
{

	switch(a_Ptr -> timer_ID)
	{
	case TIMER_0:
		TCCR0  = (TCCR0 & 0xF8) | (a_Ptr -> timer_Clock);
		break;
	case TIMER_1:
		TCCR1B  = (TCCR1B & 0xF8) | (a_Ptr -> timer_Clock);
		break;
	case TIMER_2:
		TCCR2  = (TCCR2 & 0xF8) | (a_Ptr -> timer_Clock);
		break;

	}

}
