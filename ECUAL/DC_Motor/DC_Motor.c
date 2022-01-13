/*
 * DC_Motor.c
 *
 * Created: 1/4/2022 1:11:44 PM
 *  Author: Ali Dorgham
 */ 


/**************************************************************************************************
* User defined Libraries
***************************************************************************************************/

#include "DC_Motor.h"
#include "DIO.h"
#include "DC_Motor_cfg.h"
#include "Library.h"

/**************************************************************************************************
* Extern variables
***************************************************************************************************/
extern MTR_CFG_t  Arr_ST_Mtr_cfg  [Mtr_End];

/**************************************************************************************************
* Incomplete data types
***************************************************************************************************/
typedef enum 
{
	Motor_Off,
	Motor_On
}MTR_State_t;

typedef enum 
{
	Motor_CW,  /* H1 is on , H2 is off */
	Motor_ACW  /* H2 is on , H1 is off */
}MTR_Dircetion_t;

/**************************************************************************************************
* Static Local variables
***************************************************************************************************/
static MTR_Dircetion_t   Motor_Direction [Mtr_End] = {Motor_CW, Motor_CW};
static MTR_State_t       Motor_State     [Mtr_End] = {Motor_Off, Motor_Off};


/**************************************************************************************************
* implementations of extern functions
***************************************************************************************************/

/**************************************************************************************************
* MOTOR_INIT
***************************************************************************************************/

void	MOTOR_INIT     (Motor_t   num ,STR_PWM_config_t * configurations)
{
	/* Speed Pin */
	/* set as output */
	DIO_setPinDirection(Arr_ST_Mtr_cfg[num][MOTOR_EN].PORT, Arr_ST_Mtr_cfg[num][MOTOR_EN].num_pin, DIO_u8_OUTPUT);
	/* default value is off */
	DIO_writePinValue(Arr_ST_Mtr_cfg[num][MOTOR_EN].PORT, Arr_ST_Mtr_cfg[num][MOTOR_EN].num_pin, DIO_u8_LOW);
		
	/* H1 Pin */
	/* set as output */
	DIO_setPinDirection(Arr_ST_Mtr_cfg[num][MOTOR_H1].PORT, Arr_ST_Mtr_cfg[num][MOTOR_H1].num_pin, DIO_u8_OUTPUT);
	/* default value is off */
	DIO_writePinValue(Arr_ST_Mtr_cfg[num][MOTOR_H1].PORT, Arr_ST_Mtr_cfg[num][MOTOR_H1].num_pin, DIO_u8_LOW);
		
	/* H2 Pin */
	/* set as output */
	DIO_setPinDirection(Arr_ST_Mtr_cfg[num][MOTOR_H2].PORT, Arr_ST_Mtr_cfg[num][MOTOR_H2].num_pin, DIO_u8_OUTPUT);
	/* default value is off */
	DIO_writePinValue(Arr_ST_Mtr_cfg[num][MOTOR_H2].PORT, Arr_ST_Mtr_cfg[num][MOTOR_H2].num_pin, DIO_u8_LOW);
		
		
	PWM_INIT (configurations);
	SET_PWM_DutyCycle (configurations);
	//PWM_START(configurations);

	Motor_State [num] = Motor_Off;	
}

/**************************************************************************************************
* MOTOR_CW
***************************************************************************************************/

MOTOR_ERROR_state 		MOTOR_CW      (Motor_t   num ,STR_PWM_config_t * configurations)
{
	MOTOR_ERROR_state   return_value   = Valid_MTR_init;
	/* check if num is in correct range */
	if((num < Mtr_Start) || (num > Mtr_End))
	{
		return_value   = Invalid_MTR_Num;
	}
	else
	{
		/* 1. stop the motor */
		MOTOR_Stop (num);
			
		/* 2. store the state for the next restart */
		Motor_Direction[num] = Motor_CW;
			
		/* 3. stop the motor */
		MOTOR_Start (num , configurations);
	}
	return return_value;
}

/**************************************************************************************************
* MOTOR_ACW
***************************************************************************************************/

MOTOR_ERROR_state 		MOTOR_ACW      (Motor_t   num ,STR_PWM_config_t * configurations)
{
	MOTOR_ERROR_state   return_value   = Valid_MTR_init;
	/* check if num is in correct range */
	if((num < Mtr_Start) || (num > Mtr_End))
	{
		return_value   = Invalid_MTR_Num;
	}
	else
	{
		/* 1. stop the motor */
		MOTOR_Stop (num);
			
		/* 2. store the state for the next restart */
		Motor_Direction[num] = Motor_ACW;
			
		/* 3. stop the motor */
		MOTOR_Start (num , configurations);
	}
	return return_value;
}


/**************************************************************************************************
* MOTOR_Stop
***************************************************************************************************/

MOTOR_ERROR_state 		MOTOR_Stop       (Motor_t   num )
{
	MOTOR_ERROR_state   return_value   = Valid_MTR_init;
	/* check if num is in correct range */
	if((num < Mtr_Start) || (num > Mtr_End))
	{
		return_value   = Invalid_MTR_Num;
	}
	else
	{
		/* 2. start the motor! */
		DIO_writePinValue(Arr_ST_Mtr_cfg[num][MOTOR_EN].PORT, Arr_ST_Mtr_cfg[num][MOTOR_EN].num_pin, DIO_u8_LOW);
		DIO_writePinValue(Arr_ST_Mtr_cfg[num][MOTOR_H1].PORT, Arr_ST_Mtr_cfg[num][MOTOR_H1].num_pin, DIO_u8_LOW);
		DIO_writePinValue(Arr_ST_Mtr_cfg[num][MOTOR_H2].PORT, Arr_ST_Mtr_cfg[num][MOTOR_H2].num_pin, DIO_u8_LOW);
			
		/* 2. store the state for the next re-stop */
		Motor_State[num] = Motor_Off;
	}
	return return_value;
}

/**************************************************************************************************
* implimentaion of static functions
***************************************************************************************************/

/**************************************************************************************************
* MOTOR_Start
***************************************************************************************************/

MOTOR_ERROR_state 		MOTOR_Start (Motor_t   num ,STR_PWM_config_t * configurations)
{
	MOTOR_ERROR_state   return_value   = Valid_MTR_init;
	/* check if num is in correct range */
	if((num < Mtr_Start) || (num > Mtr_End))
	{
		return_value   = Invalid_MTR_Num;
	}
	else
	{
		/* 1. Make sure Motor is Stopped */
		//DIO_writePinValue(Arr_ST_Mtr_cfg[num][MOTOR_EN].PORT, Arr_ST_Mtr_cfg[num][MOTOR_EN].num_pin, DIO_u8_LOW);
			
		/* 2. select direction from previous state */
		if(Motor_Direction[num] == Motor_CW)
		{
			DIO_writePinValue(Arr_ST_Mtr_cfg[num][MOTOR_H2].PORT, Arr_ST_Mtr_cfg[num][MOTOR_H2].num_pin, DIO_u8_LOW);
			DIO_writePinValue(Arr_ST_Mtr_cfg[num][MOTOR_H1].PORT, Arr_ST_Mtr_cfg[num][MOTOR_H1].num_pin, DIO_u8_HIGH);
		}
		else
		{
			DIO_writePinValue(Arr_ST_Mtr_cfg[num][MOTOR_H1].PORT, Arr_ST_Mtr_cfg[num][MOTOR_H1].num_pin, DIO_u8_LOW);
			DIO_writePinValue(Arr_ST_Mtr_cfg[num][MOTOR_H2].PORT, Arr_ST_Mtr_cfg[num][MOTOR_H2].num_pin, DIO_u8_HIGH);
		}
			
		//configurations->PWMCh.PortNum = Arr_ST_Mtr_cfg[num][MOTOR_EN].PORT ;
		//configurations->PWMCh.PinNum = Arr_ST_Mtr_cfg[num][MOTOR_EN].num_pin ;
			
		SET_PWM_DutyCycle(configurations);
		PWM_START(configurations);
		
		Motor_State[num] = Motor_On;
	}
	return return_value;
}


/**************************************************************************************************
* End of file
***************************************************************************************************/