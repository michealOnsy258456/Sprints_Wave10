/*
 * main.h
 *
 * Created: 1/3/2022 12:20:49 PM
 *  Author: Team 4
 */ 


#ifndef MAIN_H
#define MAIN_H


#include "Button.h"



#define  BUTTON_MOVE		Button1
#define  BUTTON_LEFT		Button2
#define  BUTTON_RIGHT		Button3

#define  BUTTON_SPEED		Button4


#define  Forward			0x01
#define  Backward			0x02
#define  LEFT				0x03
#define  RIGHT				0x04


typedef enum {Speed_0 = 0 , Speed_30 = 3 , Speed_60 = 6 , Speed_90 = 9 }Speed_t;
void App_Init(void);



void App_Update(void);




#endif /* MAIN_H */