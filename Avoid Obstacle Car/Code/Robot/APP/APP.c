#include "APP.h"

/********************************************************************
*					Local functions									*
*********************************************************************/

PRIVATE void Get_Distance(void);
PRIVATE void RobotMoving_SM(void);	

/********************************************************************
*					File Scope variables 							*
*********************************************************************/ 


PRIVATE uint8_t   u8_Status, u8_Speed;
PRIVATE uint16_t  u16_Distance;	
	
/********************************************************************
*					Functions Definitions  							*
*********************************************************************/

void APP_Init(void)
{
	GPIO_InitTypeDef  PIN_CONFIG = {.mode = GPIO_MODE_OUTPUT , .pull = GPIO_NOPULL };
	HAL_GPIO_Pin_Init(GPIOB , &PIN_CONFIG);
	Motor_Init();
	EXTI_Init(&EXIT_Handler);
	TIM_NormalModeInit(&TIMConfig);
	EXIT_INT2_CallBack(Get_Distance);
	LCD_Initializaion();
	LCD_Send_Character_WithLoc(1,1,'B');
	sei();
}


void APP_UPdate(void)
{
	RobotMoving_SM();		
}


// require to change
void Get_Distance(void)
{
	if (MCUCSR & (1<<ISC2))
	{	
		u8_Status  =0 ;
		MCUCSR &= ~(1<<ISC2);
		TIM_Start(&TIMConfig);
	}else{

		u16_Distance = (TCNT1) * 0.034/4  ;
		TIM_Stop(TIM1);
		u8_Status  =1 ;
		MCUCSR |= (1<<ISC2);
		TCNT1 = 0 ; 
	}
}


void UltrasonicTriggerDistance(void)
{
		HAL_GPIO_WRITEPIN(GPIOB , GPIO_PIN_2 , GPIO_PIN_SET );
		_delay_us(10);
		HAL_GPIO_WRITEPIN(GPIOB , GPIO_PIN_2 , GPIO_PIN_RESET);
		while(!u8_Status);	// wait until data to be ready
}
 

void RobotMoving_SM(void)
{
	static uint8_t u8_State = 0;
	 
	while(1)
	{
		switch(u8_State)
		{
			case STATE_START :			// initial state 
				for (uint16_t Loop =500; Loop > 0; Loop--)
				{
					Motor_Dir(DIR_FORWARD, Loop/5);
					_delay_ms(10);
				}
				LCD_Send_Command(LCD_COMMANED_CLEAR_LCD);
				u8_State = STATE_FORWARD; 
				break;	
					
			case STATE_FORWARD :     // Forward state  
				UltrasonicTriggerDistance();
				LCD_Send_Integer_WithLoc(1,1,u16_Distance,6);
				if (u16_Distance > Distance_50)
				{
					u8_Speed = Speed_30;
					u8_State = STATE_FORWARD;	
				}else if((u16_Distance >= Distance_30 )&&(u16_Distance <= Distance_50))
				{
					u8_Speed = Speed_80;
					u8_State = STATE_FORWARD;	
				}else
				{
					u8_Speed  = Speed_0;
					u8_State = STATE_RIGHT ; // jump to right state 
				}
				Motor_Dir(DIR_FORWARD , u8_Speed);		
				break;
			
			case  STATE_RIGHT :			// Right state 
				Motor_Dir(DIR_RIGHT , 60) ;
				_delay_ms(200);
				Motor_Dir(DIR_RIGHT , 0) ;
				_delay_ms(500);
				UltrasonicTriggerDistance();	// jump to forward state 
				if(u16_Distance >= Distance_30 )
				{
					u8_State = STATE_FORWARD ; 
				}else
				{
					u8_State = STATE_RIGHT ; // still wait in this state 			
				}				
				break;
			default: 
			break;	
			}
			_delay_ms(10);
		}
}