/*
 * Button.h
 *
 *  Created on: Jan 3, 2022
 *      Author: Micheal-Onsy
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "../../MCAL/DIO/DIO.h"
#include "../../LIBRARY/Macros.h"
#include "../../LIBRARY/std_types.h"
#include <util/delay.h>

/*******************************************************************
 *                             MACROS                              *
 ******************************************************************/
#define BUTTON1         (uint8_t)0
#define BUTTON2         (uint8_t)1
#define BUTTON3         (uint8_t)2
#define BUTTON4         (uint8_t)3
#define BUTTON5         (uint8_t)4
#define BUTTON_PUSHED   (uint8_t)0
#define BUTTON_RELEASED (uint8_t)1
#define BUTTON_PORT    	PORTb
#define BUTTON_PIN0     PIN0
#define BUTTON_PIN1     PIN1
#define BUTTON_PIN2     PIN2
#define BUTTON_PIN3     PIN3
#define BUTTON_PIN4     PIN4
#define BUTTON_PIN5     PIN5
#define BUTTON_PIN6     PIN6
#define BUTTON_PIN7     PIN7

/*******************************************************************
 *                        APIs DECLARATION                         *
 ******************************************************************/
/*- APIs DECLARATION------------------------*/
ERROR_STATE_t Button_Init(uint8_t Button_ID);
ERROR_STATE_t Button_getState(uint8_t Button_ID,uint8_t * State);

#endif /* BUTTON_H_ */
