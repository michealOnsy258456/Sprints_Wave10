/*
 * APP.c
 *
 *  Created on: Jan 19, 2022
 *      Author: Micheal-Onsy
 */

#include "APP.h"


void APP_VidInit()
{
	LCD_init(); /* initialize LCD */
	LCD_displayString("Welcome Sprints ");
	LCD_displayStringRowColumn(1,0,"This is LCD Task");

    while(1)
    {
		/* Note: we write the code before while(1) because we want to execute it only once */
    }
}
