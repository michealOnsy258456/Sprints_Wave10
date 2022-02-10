/*
 * Timer1.c
 *
 *  Created on: Jan 15, 2020
 *      Author: micheal_onsy
 */

#include "Timer.h"


/*Local Macro*/
#define CS00    0
#define CS01    1
#define CS02    2
#define WGM01   3
#define COM00   4
#define COM01   5
#define WGM00   6
#define FOC0    7

#define TOIE0   0
#define OCIE0   1
#define TOIE1   2
#define OCIE1B  3
#define OCIE1A  4
#define TICIE1  5
#define TOIE2   6
#define OCIE2   7

#define CS10    0
#define CS11    1
#define CS12    2
#define WGM12   3
#define WGM13   4
#define ICES1   6
#define ICNC1   7

#define WGM10   0
#define WGM11   1
#define FOC1B   2
#define FOC1A   3
#define COM1B0  4
#define COM1B1  5
#define COM1A0  6
#define COM1A1  7

#define CS20    0
#define CS21    1
#define CS22    2
#define WGM21   3
#define COM20   4
#define COM21   5
#define WGM20   6
#define FOC2    7

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


void TIMER_Stop(const TIM_ID a_timerID)
{

	switch(a_timerID)
	{

	case TIMER_0:
		TCCR0  = ( TCCR0 & 0xF8 );
		TCNT1=0;
		break;
	case TIMER_1:
		TCCR1B = (TCCR1B & 0xF8);
		TCNT1=0;
		break;
	case TIMER_2:
		TCCR2  = ( TCCR2 & 0xF8 );
		TCNT2=0;
		break;
	}
}

void TIMER_Start(const TIM_Clock TIME_Clk,const TIM_ID TIME_ID)
{

	switch(TIME_ID)
	{
	case TIMER_0:
		TCCR0  = (TCCR0 & 0xF8) | (TIME_Clk);
		break;
	case TIMER_1:
		TCCR1B  = (TCCR1B & 0xF8) | (TIME_Clk);
		break;
	case TIMER_2:
		TCCR2  = (TCCR2 & 0xF8) | (TIME_Clk);
		break;
	}
}

void TIMER_CLEAR_FLAG(const TIM_ID a_timerID,const TIM_Mode a_TimerMode)
{
	switch (a_timerID)
	{
	case TIMER_0:
		switch(a_TimerMode)
		{
		case NORMAL:
			break;
		case COMPARE:
			Set_Bit(TIFR_R,1);
			break;
		default:
			break;
		}
		break;
		case TIMER_1:

			break;
		case TIMER_2:
			switch(a_TimerMode)
			{
			case NORMAL:
				break;
			case COMPARE:
				Set_Bit(TIFR_R,7);
				break;
			default:
				break;
			}
			break;

			default:
			{}
			break;
	}
}



uint8_t* TIMER_Get_Status(TIM_Config * a_Ptr, char state)
{
	static uint8_t a_Flag_TIM0=0,a_Flag_TIM2=0;

	if (state==TIME0)
	{
		if(a_Flag_TIM0 == 0)
		{
			a_Flag_TIM0=1;

			return &a_Flag_TIM0 ;
		}
		else if (a_Flag_TIM0==1)
		{
			switch(a_Ptr->timer_ID)
			{
			case TIMER_0:
				switch(a_Ptr->timer_Mode)
				{
				case NORMAL:
					break;
				case COMPARE:
					if (Get_Bit(TIFR_R,1)==1)
					{
						a_Flag_TIM0=2;
						TIMER_Stop(TIMER_0);
						TIMER_CLEAR_FLAG(TIMER_0,COMPARE);
						return &a_Flag_TIM0 ;
					}
					break;
				}
				break;
				case TIMER_1:
					break;
				case TIMER_2:
					break;

			}
		}
	}
	else if (state == TIME2)
	{
		if(a_Flag_TIM2 == 0)
		{
			a_Flag_TIM2=1;

			return &a_Flag_TIM2 ;
		}
		else if (a_Flag_TIM2==1)
		{
			switch(a_Ptr->timer_ID)
			{
			case TIMER_0:
				break;
			case TIMER_1:
				break;

			case TIMER_2:
				switch(a_Ptr->timer_Mode)
				{
				case NORMAL:
					break;
				case COMPARE:
					if (Get_Bit(TIFR_R,1)==1)
					{
						a_Flag_TIM2=2;
						TIMER_Stop(a_Flag_TIM2);
						TIMER_CLEAR_FLAG(TIMER_2,COMPARE);
						return &a_Flag_TIM2 ;
					}
					break;
				}
				break;

			}
		}

	}
	switch(a_Ptr->timer_ID)
	{
	case TIMER_0:
		switch(a_Ptr->timer_Mode)
		{
		case NORMAL:
			break;
		case COMPARE:
			if (Get_Bit(TIFR_R,7)==1)
			{
				a_Flag_TIM0=2;
				TIMER_Stop(TIMER_0);
				TIMER_CLEAR_FLAG(TIMER_0,COMPARE);
				return &a_Flag_TIM0 ;
			}
			break;
		}
		break;
		case TIMER_1:
			break;
		case TIMER_2:
			switch(a_Ptr->timer_Mode)
			{
			case NORMAL:
				break;
			case COMPARE:
				if (Get_Bit(TIFR_R,7)==1)
				{
					a_Flag_TIM2=2;
					TIMER_Stop(TIMER_2);
					TIMER_CLEAR_FLAG(TIMER_2,COMPARE);
					return &a_Flag_TIM2 ;
				}
				break;
			}
			break;
			default :
				break;
	}
	return 0;
}


