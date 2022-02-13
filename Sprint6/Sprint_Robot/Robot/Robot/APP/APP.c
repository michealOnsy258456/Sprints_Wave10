/*
 * APP.c
 *
 * Created: 1/23/2022 6:21:30 PM
 *  Author: Ahmed_Ayman
 */ 


#include "APP.h"

void Get_Distance(void);

Ultrasonic_GPIOPINS_t  Ultrasonic_PINS = {.ECO_PIN.PINNum = GPIO_PIN_2 ,
											.ECO_PIN.PORT = GPIOB ,
											.TRIGGER_PIN.PINNum = GPIO_PIN_1 ,
											.TRIGGER_PIN.PORT = GPIOB };

EXIT_Handler_t  EXIT_Handler = {.EXTI_EDGE_DETECTION = EXTI_EDGE_RISING_EDGE ,.EXTI_NUM = EXTI_NUM_2};
	
	
TIMInit_t TIMConfig  ={ .Instance = TIM1 , .TimPreScaler = TIM_1_Prescaler_8};
uint8_t Edge , Status ;
	
	
void RobotMoving_SM(void);	 
void APP_Init(void)
{
	
	//Ultrasonic_Init(	&Ultrasonic_PINS );
	Motor_Init() ;
	EXTI_Init(&EXIT_Handler);
	TIM_NormalModeInit(&TIMConfig);
	EXIT_INT2_CallBack(Get_Distance);
	LCD_Initializaion();
	DDRB |= 0x02 ;
	sei();
	LCD_Send_Character_WithLoc(1,1,'B');


}
uint16_t   Distance ;

void APP_UPdate(void)
{

		RobotMoving_SM();
		
}

void Get_Distance(void)
{

	if (MCUCSR & (1<<ISC2))
	{	
		Status  =0 ;
		MCUCSR &= ~(1<<ISC2);
		TIM_Start(&TIMConfig);
	}else{

		Distance = (TCNT1) * 0.034/4  ;
		TIM_Stop(TIM1);
		Status  =1 ;
		MCUCSR |= (1<<ISC2);
		TCNT1 = 0 ; 
	}
}

void UltrasonicTriggerDistance(void)
{
	

		PORTB |= 0x02 ;
		_delay_us(10);
		PORTB = 0 ;
		_delay_ms(10);
		while(!Status);	// wait until data to be ready

}
uint8_t Speed = 0 ; 
#define Distance_50			50
#define Distance_30			30

#define Speed_30			30
#define Speed_80			80


#define STATE_FORWARD		1
#define STATE_RESET			0
#define STATE_RIGHT			2

static uint8_t State = 0 ; 
void RobotMoving_SM(void)
{

	
	
while(1)
{
	static uint8_t InerLoop = 0 ; 
	switch(State)
	{
		case STATE_RESET :			// initial state 
			for (uint16_t Loop =5000 ; Loop < 0 ; Loop--)
			{
				switch(InerLoop)
				{
					case STATE_FORWARD :     // Forward state
						UltrasonicTriggerDistance();
						LCD_Send_Integer_WithLoc(1,1,Distance,6);
						Motor_Dir(DIR_FORWARD , Loop/50) ;
						if(Distance >= Distance_30 )
						{
							InerLoop = STATE_FORWARD ;
						}else
						{
							InerLoop = STATE_RIGHT ; 		// still wait in this state
						}
					break;	
					
								
					case  STATE_RIGHT :			// Right state
						Motor_Dir(DIR_RIGHT , Loop/50) ;
						_delay_ms(200);
						Motor_Dir(DIR_RIGHT , 0) ;
						_delay_ms(500);
						UltrasonicTriggerDistance();						// jump to forward state
						if(Distance >= Distance_30 )
						{
							InerLoop = STATE_FORWARD ;
						}else
						{
							InerLoop = STATE_RIGHT ; 		// still wait in this state
						}
					break;			


			}
				_delay_ms(1);
				LCD_Send_Command(0x01);
		}
		State = STATE_FORWARD ; 
		LCD_Send_String_WithLoc(1,1,"Exit Reset");
		_delay_ms(5000) ;
			break;
			
			case STATE_FORWARD :     // Forward state  
					
					UltrasonicTriggerDistance();
					LCD_Send_Integer_WithLoc(1,1,Distance,6);
					if (Distance > Distance_50)
					{
						Speed = Speed_30 ;
						State = STATE_FORWARD;	
					}else if((Distance >= Distance_30 )&&(Distance <= Distance_50))
					{
						Speed = Speed_80 ;
						State = STATE_FORWARD;	
					}else
					{
						Speed  = 0  ;
						State = STATE_RIGHT ; // jump to right state 
					}
					Motor_Dir(DIR_FORWARD , Speed) ;
						
				break;
			
		case  STATE_RIGHT :			// Right state 
				// turn right and  temp stop
						Motor_Dir(DIR_RIGHT , 60) ;
						_delay_ms(200);			
						Motor_Dir(DIR_RIGHT , 0) ;				
						_delay_ms(500);
						UltrasonicTriggerDistance();							// jump to forward state 
				if(Distance >= Distance_30 )
				{
					State = STATE_FORWARD ; 
				}else
				{
					State = STATE_RIGHT ; 		// still wait in this state 			
				}				
			break;
		default: 
		
		
		break;	
		}
	_delay_ms(10);
	
	}
		
}