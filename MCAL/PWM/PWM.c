/*
 * PWM.c
 *
 * Created: 1/13/2022 10:15:37 PM
 *  Author: Ali Hassan Dorgham
 */ 

#include "PWM.h"
#include "timer.h"

typedef struct
{
	uint8_t  port;
	uint8_t  pin;	
}PWM_PORT_PIN_t;

PWM_PORT_PIN_t   PWM_CFG  [2] = {{PORTd, PIN4},{PORTd, PIN5}};
enuTIMER_ID_t    PWM_TIMERS [2] = {TIMER_0, TIMER_1};
typedef struct
{
	uint8_t duty_cycle;
	uint16_t pwm_frequency;
	PWM_ID pwm_ID;
	uint8_t pin_state;
	uint8_t port_ID;
	uint8_t pin_ID;
}PWM_ConfigType;

static void     PWM_init_I_(const PWM_ConfigType * Config_Ptr);//DONE
static void		PWM_setCallBack(void(*a_ptr)(void), const PWM_ID a_pwmID);//DONE
static void		PWM_start(const PWM_ID a_pwmID, const enuTIMER_Clock_t a_timerClock);
static uint16_t PWM_setDutyCycle(const PWM_ConfigType * Config_Ptr);

static void     TOGGLE_1 (void);
static void     TOGGLE_2 (void);

static void (*PWM_CALLBACKS[])(void) = {TOGGLE_1,TOGGLE_2};

void PWM_Init(PWM_ID pwm_ch, uint64_t Frequency)
{
	DIO_setPinDirection(PWM_CFG[pwm_ch].port, PWM_CFG[pwm_ch].pin, DIO_u8_OUTPUT);
	DIO_writePinValue(PWM_CFG[pwm_ch].port, PWM_CFG[pwm_ch].pin, DIO_u8_LOW);
	
	
	PWM_ConfigType  Config_Ptr;
	Config_Ptr.duty_cycle = 0;
	Config_Ptr.pin_ID = PWM_CFG[pwm_ch].pin;
	Config_Ptr.pin_state = 1;
	Config_Ptr.port_ID = PWM_CFG[pwm_ch].port;
	Config_Ptr.pwm_frequency = FREQ_1K;
	Config_Ptr.pwm_ID = PWM_TIMERS[pwm_ch];
	PWM_init_I_(&Config_Ptr);

	PWM_setCallBack(PWM_CALLBACKS[pwm_ch], pwm_ch);
}

void PWM_Stop(PWM_ID pwm_ch)
{
	DIO_writePinValue(PWM_CFG[pwm_ch].port, PWM_CFG[pwm_ch].pin, DIO_u8_LOW);
	TIMER_stop(pwm_ch);
}

void SET_PWM_DutyCycle(PWM_ID pwm_ch, uint8_t Duty)
{
	DIO_writePinValue(PWM_CFG[pwm_ch].port, PWM_CFG[pwm_ch].pin, DIO_u8_HIGH);
	/*
	some code
	*/
	PWM_ConfigType  Config_Ptr;
	Config_Ptr.duty_cycle = Duty;
	Config_Ptr.pin_ID = PWM_CFG[pwm_ch].pin;
	Config_Ptr.pin_state = 1;
	Config_Ptr.port_ID = PWM_CFG[pwm_ch].port;
	Config_Ptr.pwm_frequency = FREQ_1K;
	Config_Ptr.pwm_ID = PWM_TIMERS[pwm_ch];
	
	strTIMER_ConfigType_t timer_Config;
	
	timer_Config.intialValue = 0;
	timer_Config.compareValue = PWM_setDutyCycle(&Config_Ptr);
	timer_Config.timer_ID = Config_Ptr.pwm_ID;
	timer_Config.timer_Mode = COMPARE;
	TIMER_init(&timer_Config);
	
	TIMER_start(pwm_ch, T0_F_CPU_CLOCK);
}

/***************************************************************************************************************/

static void PWM_init_I_(const PWM_ConfigType * Config_Ptr)
{
	strTIMER_ConfigType_t timer_Config;

	timer_Config.intialValue = 0;
	/* This function can only be used when T "high" is multiple of T "low" */
	timer_Config.compareValue = PWM_setDutyCycle(Config_Ptr);
	timer_Config.timer_ID = Config_Ptr->pwm_ID;
	timer_Config.timer_Mode = COMPARE;

	/* Configure PWM channel to be an output pin */
	DIO_setPinDirection(Config_Ptr->port_ID, Config_Ptr->pin_ID, DIO_u8_OUTPUT);

	/* Write the initial state of the PWM channel */
	DIO_writePinValue(Config_Ptr->port_ID, Config_Ptr->pin_ID, Config_Ptr->pin_state);

	/* Configure TIMER */
	TIMER_init(&timer_Config);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
static void PWM_setCallBack(void(*a_ptr)(void), const PWM_ID a_pwmID)
{
	TIMER_setCallBack(a_ptr, a_pwmID);
}

static uint16_t PWM_setDutyCycle(const PWM_ConfigType * Config_Ptr)
{
	uint16_t result;

	/* In case of PWM0 and PWM2 you should use frequency larger than or equal to 1k Hz */
	if	((Config_Ptr->pwm_ID == PWM_0 || Config_Ptr->pwm_ID == PWM_2) && (Config_Ptr->pwm_frequency >= FREQ_1K))
	{
		result = (uint8_t)(((Config_Ptr->duty_cycle) * F_CPU)/(100UL * (Config_Ptr->pwm_frequency)));
	}
	else if(Config_Ptr->pwm_ID == PWM_1)
	{
		result = (uint16_t)(((Config_Ptr->duty_cycle) * F_CPU)/(100UL * (Config_Ptr->pwm_frequency)));
	}
	return result;
}

static void     TOGGLE_1 (void)
{
	DIO_TogglePin(PWM_CFG[0].port, PWM_CFG[0].pin);
}

static void     TOGGLE_2 (void)
{
	DIO_TogglePin(PWM_CFG[1].port, PWM_CFG[1].pin);
}