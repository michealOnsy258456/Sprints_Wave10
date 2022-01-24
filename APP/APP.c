/*
 * APP.c
 *
 *  Created on: Jan 19, 2022
 *      Author: Micheal-Onsy
 */

#include "APP.h"


void APP_VidInit()
{
	uint8_t Number;
	LED_Init(LED0);
	LED_Init(LED1);
	LED_Init(LED2);
	LED_Init(LED3);

	while(1)
	{
		KeyPad_getPressedKey(&Number);
		switch(Number)
		{
		case 1:
			LED_AllClose();
			LED_Open(LED0);
			break;
		case 2:
			LED_AllClose();
			LED_Open(LED1);

			break;
		case 3:
			LED_AllClose();
			LED_Open(LED0);
			LED_Open(LED1);
			break;
		case 4:
			LED_AllClose();
			LED_Open(LED2);

			break;
		case 5:
			LED_AllClose();
			LED_Open(LED0);
			LED_Open(LED2);

			break;
		case 6:
			LED_AllClose();
			LED_Open(LED1);
			LED_Open(LED2);
			break;
		case 7:
			LED_AllClose();
			LED_Open(LED0);
			LED_Open(LED1);
			LED_Open(LED2);
			break;
		case 8:
			LED_AllClose();
			LED_Open(LED3);
			break;
		case 9:
			LED_AllClose();
			LED_Open(LED0);
			LED_Open(LED3);
			break;
		}
	}

}
