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
#include "../../LIBRARY/Macros.h"
#include "../../LIBRARY/std_types.h"

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
ERROR_STATE_t LED_On(uint8_t LED_ID);
ERROR_STATE_t LED_Off(uint8_t LED_ID);
#endif /* LED_H_ */
