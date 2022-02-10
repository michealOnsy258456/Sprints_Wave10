/*
 * Timer1.h
 *
 *  Created on: Jan 15, 2020
 *      Author: micheal_onsy
 */

#ifndef TIMER_H_
#define TIMER_H_


/*- INCLUDES
----------------------------------------------*/


#include "../../LIBRARY/std_types.h"
#include "../../LIBRARY/Register.h"
#include "../../LIBRARY/Macros.h"



/*- Types Declaration
----------------------------------------------*/
typedef enum
{
	TIMER_0, TIMER_1 ,TIMER_2
}TIM_ID;

typedef enum
{
	NORMAL, COMPARE
}TIM_Mode;

typedef enum
{
	TIMER0_NO_CLK = 0,TIMER0_F_CLK_CPU,TIMER0_F_CLK_8,TIMER0_F_CLK_64,TIMER0_F_CLK_256,TIMER0_F_CLK_1024,
	TIMER2_NO_CLK = 0,TIMER2_F_CLK1,TIMER2_F_CLK_8,TIMER2_F_CLK_32,TIMER2_F_CLK_64,TIMER2_F_CLK_128,
	TIMER2_F_CLK_256,TIMER2_F_CLK_1024,
	TIMER1_NO_CLK=0,TIMER1_F_CLK_CPU,TIMER1_F_CLK_8,TIMER1_F_CLK_64,TIMER1_F_CLK_256,TIMER1_F_CLK_1024
}TIM_Clock;

typedef struct
{
	TIM_ID timer_ID;
	TIM_Mode timer_Mode;
	TIM_Clock timer_Clock;
}TIM_Config;

#define TIME0 1
#define TIME2 2

/******************************************************************************
 *                          Functions Prototypes                              *
 ******************************************************************************/

void TIMER_VidInit(const TIM_Config * a_Ptr,uint16_t a_SetInitialValue,uint16_t a_SetCompare);
void TIMER_Start(const TIM_Clock TIME_Clk,const TIM_ID TIME_ID);
void TIMER_Stop(const TIM_ID a_timerID);
void TIMER_setCallBack(void(*a_ptr)(void), const TIM_ID a_timerID);
void TIMER_CLEAR_FLAG(const TIM_ID a_timerID,const TIM_Mode a_TimerMode);
uint8_t* TIMER_Get_Status(TIM_Config * a_Ptr,char state);

#endif /* TIMER_H_ */

