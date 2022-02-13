/*
 * APP.h
 *
 * Created: 1/23/2022 6:21:17 PM
 *  Author: Ahmed_Ayman
 */ 


#ifndef APP_H_
#define APP_H_


#include <avr/io.h>
#include "HAL_GPIO.h"
#include "HAL_EXIT.h"
#include "TIMER_Interface.h"
#include "Motor.h"
#include <stdlib.h>
#include "Ultrasonic.h"
#include "Lcd-Driver.h"





void APP_Init(void);


void APP_UPdate(void);



#endif /* APP_H_ */