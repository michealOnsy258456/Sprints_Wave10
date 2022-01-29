/*
 * LED.h
 *
 *  Created on: Jan 3, 2022
 *      Author: Micheal-Onsy
 */

#ifndef LED_H_
#define LED_H_

/*- INCLUDES
----------------------------------------------*/
#include "../../MCAL/DIO/DIO.h"

/*- MACROS------------------------*/
#define LED0     	 0
#define LED1     	 1
#define LED2      	 2
#define LED3      	 3
#define LED_PORT     PORTb
#define LED_PIN4     PIN4
#define LED_PIN5     PIN5
#define LED_PIN6     PIN6
#define LED_PIN7     PIN7

/*- FUNCTION DECLARATIONS ----------------------------------*/
ERROR_STATE_t LED_Init(uint8_t LED_ID);
ERROR_STATE_t LED_toggle(uint8_t LED_ID);
ERROR_STATE_t LED_Close(uint8_t LED_ID);
ERROR_STATE_t LED_Open(uint8_t LED_ID);
ERROR_STATE_t LED_AllOpen();
ERROR_STATE_t LED_AllClose();


#endif /* LED_H_ */
