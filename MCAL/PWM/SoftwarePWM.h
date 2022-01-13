/*
 * SoftwarePWM.h
 *
 * Created: 1/7/2022 9:43:46 PM
 *  Author: Ahmed_Ayman
 */ 


#ifndef SOFTWAREPWM_H_
#define SOFTWAREPWM_H_

#include "timer.h"
#include "DIO.h"


typedef enum {TIM_OK , TIM_ERROR}PWM_ERROR_state_t;

typedef struct 
{
	uint8_t PinNum	;
	uint8_t PortNum ;		
}str_PWMCh_t;

typedef struct{
	TIMER_ID TIMInstance ; 	
	uint8_t Freq	;	 
	str_PWMCh_t PWMCh ; 
	uint8_t DutyCycle ; 	
}STR_PWM_config_t;


PWM_ERROR_state_t PWM_INIT (const STR_PWM_config_t * configurations);
PWM_ERROR_state_t PWM_START (const STR_PWM_config_t * configurations);
PWM_ERROR_state_t PWM_STOP (const STR_PWM_config_t * configurations);
PWM_ERROR_state_t SET_PWM_DutyCycle (const STR_PWM_config_t * configurations);


#endif /* SOFTWAREPWM_H_ */