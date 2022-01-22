/*
 * APP.c
 *
 *  Created on: Jan 19, 2022
 *      Author: Micheal-Onsy
 */

#include "APP.h"
void APP_VidInit()
{
	uint16_t res_value;
	LCD_init(); /* initialize LCD driver */
	ADC_Init(); /* initialize ADC driver */
	LCD_clearScreen(); /* clear LCD at the beginning */
	/* display this string "ADC Value = " only once at LCD */
	LCD_displayString("ADC Value = ");
	while(1)
	{
		LCD_goToRowColumn(0,12); /* display the number every time at this position */
		ADC_Read(0,&res_value); /* read channel zero where the potentiometer is connect */
		LCD_VidWriteNumber(res_value); /* display the ADC value on LCD screen */
		LCD_displayString("    ");
	}

}
