/*
 * APP.c
 *
 *  Created on: Jan 24, 2022
 *      Author: Micheal-Onsy
 */
#include "APP.h"


/*GLOBAL VARIABLE
----------------------------*/
uint8_t data='A';

void App_Init(void){

	TWI_Init();
}
void App_Update(void)
{
	TWI_SendChar(24,data);
}
