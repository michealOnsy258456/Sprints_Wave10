#include "App.h"

static STR_PWM_config_t     configurations[Mtr_End] = {0};
static Car_StateMachine_t   CAR          = CAR_EN_Stop;
static Car_StateMachine_t   CAR_Gear     = CAR_EN_Stop;
static uint8_t              speed    [4] = {0, 30, 60, 90};

static void  APP_Apply(void);

void App_Init(void)
{
	configurations[Motor1].DutyCycle		= 0;
	configurations[Motor1].TIMInstance		= TIMER_0;
	configurations[Motor1].Freq				= 0x03;
	configurations[Motor1].PWMCh.PortNum	= MTR_1_EN_PORT;
	configurations[Motor1].PWMCh.PinNum		= MTR_1_EN;
	
	configurations[Motor2].DutyCycle		= 0;
	configurations[Motor2].TIMInstance		= TIMER_2;
	configurations[Motor2].Freq				= 0x03;
	configurations[Motor2].PWMCh.PortNum	= MTR_2_EN_PORT;
	configurations[Motor2].PWMCh.PinNum		= MTR_2_EN;
	
	BUTTON_init();
	MOTOR_INIT(Motor1 , &configurations[Motor1] );
	MOTOR_INIT(Motor2 , &configurations[Motor2] );	
}

void App_Update(void)
{  
	BTN_State_t  BTN_value = BTN_LOW;
	switch (CAR_Gear)
	{
		case CAR_EN_Stop:
		{
			//check transfer conditions
			BUTTON_READ (BUTTON_GEAR, &BTN_value);
			if(BTN_value == BTN_HIGH)
			{
				CAR_Gear = CAR_EN_F_30;
			}
			else{/*MISRA C*/}
		}break;
		case CAR_EN_F_30:
		{
			//check transfer conditions
			BUTTON_READ (BUTTON_GEAR, &BTN_value);
			if(BTN_value == BTN_HIGH)
			{
				CAR_Gear = CAR_EN_F_60;
			}
			else{/*MISRA C*/}
		}break;
		case CAR_EN_F_60:
		{
			//check transfer conditions
			BUTTON_READ (BUTTON_GEAR, &BTN_value);
			if(BTN_value == BTN_HIGH)
			{
				CAR_Gear = CAR_EN_F_90;
			}
			else{/*MISRA C*/}
			
		}break;
		case CAR_EN_F_90:
		{
			//check transfer conditions
			BUTTON_READ (BUTTON_GEAR, &BTN_value);
			if(BTN_value == BTN_HIGH)
			{
				CAR_Gear = CAR_EN_B_30;
			}
			else{/*MISRA C*/}
		}break;
		case CAR_EN_B_30:
		{
			//check transfer conditions
			BUTTON_READ (BUTTON_GEAR, &BTN_value);
			if(BTN_value == BTN_HIGH)
			{
				CAR_Gear = CAR_EN_F_30;
			}
			else{/*MISRA C*/}					
		}break;
		default:{/*MISRA C*/}
	}
	switch(CAR)
	{	
		case CAR_EN_Move:
		{
			//action of Motors
			APP_Apply();
			//check transfer conditions
			BUTTON_READ (BUTTON_MOVE, &BTN_value);
			if(BTN_value == BTN_HIGH)
			{
				CAR = CAR_EN_Move;
			}
			else
			{
				CAR = CAR_EN_Stop;
			}
		}break;
		case CAR_EN_Right:
		{
			//action of Motors
			APP_Apply();
			//check transfer conditions
			BUTTON_READ (BUTTON_RIGHT, &BTN_value);
			if(BTN_value == BTN_HIGH)
			{
				CAR = CAR_EN_Right;
			}
			else
			{
				CAR = CAR_EN_Stop;
			}
		}break;
		case CAR_EN_Left:
		{
			//action of Motors
			APP_Apply();
			//check transfer conditions
			BUTTON_READ (BUTTON_LEFT, &BTN_value);
			if(BTN_value == BTN_HIGH)
			{
				CAR = BUTTON_LEFT;
			}
			else
			{
				CAR = CAR_EN_Stop;
			}
		}break;
		case CAR_EN_Stop :
		{
			
			//priority 1
			//check transfer conditions
			BUTTON_READ (BUTTON_MOVE, &BTN_value);
			if(BTN_value == BTN_HIGH)
			{
				CAR = CAR_EN_Move;
			}
			else
			{
				//priority 2
				//check transfer conditions
				BUTTON_READ (BUTTON_RIGHT, &BTN_value);
				if(BTN_value == BTN_HIGH)
				{
					CAR = CAR_EN_Right;
				}
				else
				{
					//priority 3
					//check transfer conditions
					BUTTON_READ (BUTTON_LEFT, &BTN_value);
					if(BTN_value == BTN_HIGH)
					{
						CAR = CAR_EN_Left;
					}
					else
					{
						CAR = CAR_EN_Stop;
					}
				}
			}
			//action of Motors
			APP_Apply();
		}
		default:{break;}
	}	
}

static void  APP_Apply(void)
{
	Car_StateMachine_t   CAR_Gear_Previous = CAR_Gear;
	if(CAR_Gear == CAR_EN_B_30)
	{
		CAR_Gear = 1;//speed [1] = 30; but backword direction
	}
	else{/*MISRA C*/}
	configurations[Motor1].DutyCycle =  speed[CAR_Gear];
	configurations[Motor2].DutyCycle =  speed[CAR_Gear];
	switch (CAR)
	{
		case CAR_EN_Stop:
		{
			configurations[Motor1].DutyCycle =  0;
			MOTOR_Stop(Motor1);
			MOTOR_Start(Motor1, &configurations[Motor1]);
			
			configurations[Motor2].DutyCycle =  0;
			MOTOR_Stop(Motor2);
			MOTOR_Start(Motor2, &configurations[Motor2]);
		}break;
		case CAR_EN_Move:
		{
			MOTOR_CW(Motor1 ,&configurations[Motor1]);
			MOTOR_CW(Motor2 ,&configurations[Motor2]);
		}break;
		case CAR_EN_Right:
		{
			configurations[Motor2].DutyCycle =  0;
			MOTOR_Stop(Motor2);
			MOTOR_Start(Motor2, &configurations[Motor2]);
			
			MOTOR_CW(Motor1 ,&configurations[Motor1]);
		}break;
		case CAR_EN_Left:
		{
			configurations[Motor1].DutyCycle =  0;
			MOTOR_Stop(Motor1);
			MOTOR_Start(Motor1, &configurations[Motor1]);
			
			MOTOR_CW(Motor2 ,&configurations[Motor2]);
		}break;
		default:
		{
			if(CAR_Gear_Previous == CAR_EN_B_30)
			{
				MOTOR_ACW(Motor1 ,&configurations[Motor1]);
				MOTOR_ACW(Motor2 ,&configurations[Motor2]);
			}
			else{/*MISRA C*/}
		}break;
	}
	CAR_Gear = CAR_Gear_Previous;
}