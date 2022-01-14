/*
 * 	main.c
 *
 *  Created on: Jan 2, 2022
 *  Author: Micheal-Onsy
 */


#include"HAL/BUTTON/Button.h"
#include"HAL/LED/LED.h"
#include <util/delay.h>
/*- MAIN -----------------------------------------------*/
int main() {
	uint8_t u8_PushedButton = BUTTON_RELEASED;
	/*LED INIT*/
	LED_Init(LED2);
	/*BUTTON INIT*/
	Button_Init(BUTTON1);
	while (1) {
        /*GET THE PUSH BUTTON STATUS*/
		Button_getState(BUTTON1,&u8_PushedButton);

		/*CHECK IF THE BUTTON IS PUSHED*/
		if (BUTTON_PUSHED==u8_PushedButton)//IF PESSED
		{
	        /*WAIT 200ms FOR DEBOUNCE*/
			_delay_ms(200);
		    /*GET THE STATUS AGAIN*/
			Button_getState(BUTTON1,&u8_PushedButton);
			/*CHECK IF THE BUTTON IS RELEASED*/
			if (BUTTON_RELEASED==u8_PushedButton)
            {
                /*TOGGLE LED2*/
				LED_toggle(LED2);
			}
		}
	}
	return 0;
}
