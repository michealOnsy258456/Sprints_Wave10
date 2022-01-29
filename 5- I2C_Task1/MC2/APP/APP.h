/******************************************************************************
 *
 * [MODULE]: APPLICATION
 *
 * [FILE NAME]: App.c
 *
 * [DESCRIPTION]: Source file for the Application
 *
 * [AUTHOR]: Micheal Onsy
 *
 *******************************************************************************/


#ifndef APP_APP_H_
#define APP_APP_H_

/*******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/
#include"../MCAL/GLOBAL_INTERRUPT/globalInterrupt.h"
#include "../MCAL/I2C/i2c.h"
#include "../MCAL/DIO/DIO.h"


/*******************************************************************************
 *                             Functions Prototypes                            *
 *******************************************************************************/
void APP_Init(void);
void APP_Update(void);
void TWI_ISR(void);

#endif /* APP_APP_H_ */
