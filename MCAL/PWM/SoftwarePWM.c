/*
 * SoftwarePWM.c
 *
 * Created: 1/7/2022 9:43:36 PM
 *  Author: Ahmed_Ayman
 */ 
#include "SoftwarePWM.h"
#include "stddef.h"



static  TIMER_ConfigType PWM_TIMConfig_TIM0 = { .timer_Mode = COMPARE  } , PWM_TIMConfig_TIM2 = { .timer_Mode = COMPARE  } ;
static  STR_PWM_config_t  Static_configurations_TIM0 , Static_configurations_TIM2 ;
static  uint8_t Duty_TIM0 = 0 , Duty_TIM2=0  ;

 


void GPIO_TOGGLE_TIM0(void)
{
	
	static uint8_t ON = 0 ; 
	if(ON == 0 )
	{
		OCR0 = Duty_TIM0 ; 
		ON = 1 ; 
	}
	else
	{
		OCR0 = 255 - Duty_TIM0 ;
		ON = 0 ;
	}
	DIO_TogglePin(Static_configurations_TIM0.PWMCh.PortNum, Static_configurations_TIM0.PWMCh.PinNum);
}

void GPIO_TOGGLE_TIM2(void)
{
	
	static uint8_t ON = 0 ;
	DIO_TogglePin(Static_configurations_TIM2.PWMCh.PortNum, Static_configurations_TIM2.PWMCh.PinNum);
	if(ON == 0 )
	{
		OCR2 = Duty_TIM2 ;
		ON = 1 ;
	}
	else
	{
		OCR2 = 255 - Duty_TIM2 ;
		ON = 0 ;
	}
}

PWM_ERROR_state_t PWM_INIT (const STR_PWM_config_t * configurations)
{
	float temp;
	if(configurations == NULL)
	{
		return  TIM_ERROR ;
	}
	if(configurations->TIMInstance == TIMER_0)
	{
		Static_configurations_TIM0.DutyCycle = configurations->DutyCycle ;
		Static_configurations_TIM0.PWMCh.PinNum =  configurations->PWMCh.PinNum  ;
		Static_configurations_TIM0.PWMCh.PortNum = configurations->PWMCh.PortNum ;
		if(configurations->DutyCycle != 0)
		{
			temp = ((configurations->DutyCycle*255ul)/100.0);
		}
		else
		{
			temp = 0;
		}
		Duty_TIM0 = temp;
		PWM_TIMConfig_TIM0.timer_Clock = configurations->Freq;
		PWM_TIMConfig_TIM0.timer_ID = 	configurations->TIMInstance ;
		TIMER_init(&PWM_TIMConfig_TIM0);	
		TIMER_setCallBack(GPIO_TOGGLE_TIM0 , PWM_TIMConfig_TIM0.timer_ID) ;
		DIO_setPinDirection(configurations->PWMCh.PortNum, configurations->PWMCh.PinNum ,DIO_u8_OUTPUT);	
	}
	else if (configurations->TIMInstance == TIMER_2)
	{
		Static_configurations_TIM2.DutyCycle = configurations->DutyCycle ;
		Static_configurations_TIM2.PWMCh.PinNum =  configurations->PWMCh.PinNum  ;
		Static_configurations_TIM2.PWMCh.PortNum = configurations->PWMCh.PortNum ;			
		if(configurations->DutyCycle != 0)
		{
			temp = ((configurations->DutyCycle*255ul)/100.0);
		}
		else
		{
			temp = 0;
		}
		Duty_TIM2 = temp;
		PWM_TIMConfig_TIM2.timer_Clock = configurations->Freq;
		PWM_TIMConfig_TIM2.timer_ID = 	configurations->TIMInstance ;
		TIMER_init(&PWM_TIMConfig_TIM2);	
		TIMER_setCallBack(GPIO_TOGGLE_TIM2 , PWM_TIMConfig_TIM2.timer_ID) ;
		DIO_setPinDirection(configurations->PWMCh.PortNum, configurations->PWMCh.PinNum ,DIO_u8_OUTPUT);
	}
	else
	{
		return TIM_ERROR ;
	}
	return TIM_OK ;
}

PWM_ERROR_state_t PWM_START (const STR_PWM_config_t * configurations)
{
	if (configurations == NULL)
	{
		return TIM_ERROR;
	}
	else 
	{
		if(configurations->TIMInstance == TIMER_0 )
		{
			if(TIMER_start(&PWM_TIMConfig_TIM0) != E_TIMER_SUCCESS ) 
			{
				return TIM_ERROR ; 
			}
			else
			{
				sei();	
			}
		}
		else if(configurations->TIMInstance == TIMER_2 )
		{
			if(TIMER_start(&PWM_TIMConfig_TIM2) != E_TIMER_SUCCESS )
			{
				return TIM_ERROR ;
			}
			else
			{
				sei();	
			}
		}
	}
	return TIM_OK ; 
}


PWM_ERROR_state_t PWM_STOP (const STR_PWM_config_t * configurations)
{
	
	if (configurations == NULL)
	{
		return TIM_ERROR;
	}
	if(TIMER_stop(configurations->TIMInstance) != E_TIMER_SUCCESS)
	{
		return TIM_ERROR ;
	}
	else
	{
		return TIM_OK;
	}
	return TIM_OK ;
}

PWM_ERROR_state_t SET_PWM_DutyCycle (const STR_PWM_config_t * configurations)
{	
	float temp;
	if(configurations->TIMInstance == TIMER_0 )
	{
		if(configurations->DutyCycle != 0)
		{
			temp = ((configurations->DutyCycle*255ul)/100.0);
		}
		else
		{
			temp = 0;
		}
		Duty_TIM0 = temp;
		OCR0 = Duty_TIM0 ;
			
	}else if(configurations->TIMInstance == TIMER_2 )
	{
		if(configurations->DutyCycle != 0)
		{
			temp = ((configurations->DutyCycle*255ul)/100.0);
		}
		else
		{
			temp = 0;
		}
		Duty_TIM2 = temp;
		OCR2 = Duty_TIM2 ;
	}
	else{/*MISRA C*/}
	//PWM_START(configurations);
	return TIM_OK ;
}