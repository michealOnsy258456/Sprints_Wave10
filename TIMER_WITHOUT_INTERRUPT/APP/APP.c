/*
 * APP.c
 *
 *  Created on: Jan 11, 2022
 *      Author: Micheal-Onsy
 */


#include "APP.h"


unsigned char g_tick = 0;

/*- Application Function------------------------*/
void App_VidInit()
{
	/*TIMER1 Configuration */
	TIM_Config timer_config = { TIMER_1, COMPARE, TIMER1_F_CLK_256};
	/*TIMER Function Configuration */
	TIMER_VidInit(&timer_config,0,3125);
	/*To Execute The Timer To Put Initial Value In Clock  */
	TIMER_Start(&timer_config);
	/*LED Function Configuration*/
	LED_Init(LED2);
	/* Set pin 0 in PORTC with value 0 at the beginning (LED OFF) */
	LED_Off(LED2);

}
/*- LOCAL FUNCTIONS IMPLEMENTATION------------------------*/

/*THIS FUNCTIONS TOGGLES PIN 300 MS ON AND 500 MS OFF IN CTC MODE*/
void CTC_TGL_FUNC(void)
{
	g_tick++;
	if(g_tick == 3)
	{
		LED_Off(LED2);
	}
	else if (g_tick==8)
	{
		LED_On(LED2);
		g_tick=0;
	}
}
