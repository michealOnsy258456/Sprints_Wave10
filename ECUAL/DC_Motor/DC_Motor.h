/*
 * DC_Motor.h
 *
 * Created: 1/4/2022 1:11:44 PM
 *  Author: Ali Dorgham
 */ 

#ifndef BUTTON_H_
#define BUTTON_H_

/**************************************************************************************************
* Local data types
***************************************************************************************************/
#include "SoftwarePWM.h" 
#include "DC_Motor_cfg.h"

typedef enum
{
	Mtr_Start,
	Motor1 = Mtr_Start,
	Motor2,
	Mtr_End
}Motor_t;


typedef enum 
{
	Valid_MTR_init      = 0x00,
	Invalid_MTR_Num     = 0x01,
	Invalid_Direct      = 0x02,
	MOTOR_WAS_ON        = 0x04,
	MOTOR_WAS_OFF       = 0x08,
	MOTOR_Dir_CW        = 0x10,
	MOTOR_Dir_ACW       = 0x20
}MOTOR_ERROR_state;


/**************************************************************************************************
* Extern Functions
***************************************************************************************************/

void             		MOTOR_INIT		(Motor_t   num ,STR_PWM_config_t * configurations);
MOTOR_ERROR_state 		MOTOR_Start		(Motor_t   num ,STR_PWM_config_t * configurations);
MOTOR_ERROR_state 		MOTOR_CW        (Motor_t   num ,STR_PWM_config_t * configurations);
MOTOR_ERROR_state 		MOTOR_ACW       (Motor_t   num ,STR_PWM_config_t * configurations);
MOTOR_ERROR_state 		MOTOR_Stop      (Motor_t   num);


#endif /* BUTTON_H */