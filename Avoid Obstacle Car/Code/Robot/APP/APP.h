/*
 * APP.h
 *
 * Created: 1/23/2022 6:21:17 PM
 *  Author: Ahmed_Ayman
 */ 


#ifndef APP_H_
#define APP_H_

#include "gpio.h"
#include "Motor.h"
#include "ultrasonic.h"
#include "lcd.h"
#include "SW_PWM.h"
#include "Std_Library.h"
#include "timer_Lcfg.h"
#include "external_interrupt_Lcfg.h"

#define Distance_50			50
#define Distance_30			30
#define Speed_30			30
#define Speed_80			80
#define Speed_0				0
#define STATE_START			0
#define STATE_FORWARD		1
#define STATE_RIGHT			2
#define Distance_50			50
#define Distance_30			30



void APP_Init(void);
void APP_UPdate(void);


#endif /* APP_H_ */