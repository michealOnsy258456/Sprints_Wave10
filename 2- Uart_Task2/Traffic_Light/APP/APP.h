/*
 * APP.h
 *
 *  Created on: Jan 24, 2022
 *      Author: Micheal-Onsy
 */

#ifndef APP_APP_H_
#define APP_APP_H_

#include "UART.h"
#include "LED.h"
#include "string.h"

#define GREEN   1
#define YELLOW  2
#define RED		3
#define AT		4
void AppInit(void);
void AppUpdate(void);
void APP_ClearBuffer(void);



#endif /* APP_APP_H_ */