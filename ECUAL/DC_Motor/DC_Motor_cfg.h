/*
 * DC_Motor_cfg.h
 *
 * Created: 1/4/2022 1:11:44 PM
 *  Author: Ali Dorgham
 */ 

#ifndef BUTTON_CFG_H_
#define BUTTON_CFG_H_

/**************************************************************************************************
* User defined Libraries
***************************************************************************************************/
#include "Library.h"
#include "DIO.h"


/**************************************************************************************************
* File Configurations
***************************************************************************************************/

/*
* Using H-Bridge to control DC Motor direction, so there are two pins H1, H2
* To Enable Motor using Pin EN  
*/

/* Control Pins */
#define MOTOR_EN            0
#define MOTOR_H1            1
#define MOTOR_H2            2
#define MOTOR_CONTROL_PINS   3

/* Motor 1 */
#define MTR_1_EN_PORT       PORTd
#define MTR_1_EN            PIN4

#define MTR_1_H1_PORT    	PORTd
#define MTR_1_H1         	PIN2
	
#define MTR_1_H2_PORT    	PORTd
#define MTR_1_H2         	PIN6

/* Motor 2 */
#define MTR_2_EN_PORT  	    PORTd
#define MTR_2_EN       	    PIN5

#define MTR_2_H1_PORT    	PORTd
#define MTR_2_H1         	PIN3
	
#define MTR_2_H2_PORT    	PORTd
#define MTR_2_H2         	PIN7


/**************************************************************************************************
* User data type
***************************************************************************************************/

typedef struct
{
	/* ports of speed pin */
	uint8_t PORT;
	uint8_t num_pin;
}MTR_Pins_CFG_t;

typedef MTR_Pins_CFG_t  MTR_CFG_t [MOTOR_CONTROL_PINS];

#endif /* BUTTON_CFG_H */