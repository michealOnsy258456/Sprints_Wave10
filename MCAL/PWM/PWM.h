/*
 * PWM.h
 *
 * Created: 1/13/2022 10:15:51 PM
 *  Author: Ali Hassan Dorgham
 */ 


#ifndef PWM_H_
#define PWM_H_


#include "DIO.h"


typedef enum
{
	FREQ_500 = 500, FREQ_600 = 600, FREQ_700 = 700, FREQ_800 = 800, FREQ_900 = 900,
	FREQ_1K = 1000, FREQ_2K = 2000, FREQ_3K = 3000, FREQ_4K = 4000, FREQ_5K = 5000
}PWM_Frequency;


typedef enum
{
	PWM_0, PWM_1, PWM_2
}PWM_ID; 

void PWM_Init(PWM_ID pwm_ch, uint64_t Frequency);
void PWM_Stop(PWM_ID pwm_ch);
void SET_PWM_DutyCycle(PWM_ID pwm_ch, uint8_t Duty);



#endif /* PWM._H_ */