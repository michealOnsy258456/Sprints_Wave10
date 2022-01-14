/*
 * main.c
 *
 *  Created on: Jan 4, 2022
 *      Author: Micheal-Onsy
 */
#include "APP/APP.h"
#include"MCAL/TIMER/Timer.h"

/*- MAIN------------------------*/
int main()
{
	uint8_t State=0;
	App_VidInit();

	while(1)
	{
		TIMER_Get_Status(TIMER_1,COMPARE,&State);

		if (State==1)
		{
			CTC_TGL_FUNC();
			State=0;
		}
	}
}


