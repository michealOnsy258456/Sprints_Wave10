 /******************************************************************************
 *
 * [MODULE]: APPLICATION
 *
 * [FILE NAME]: App.h
 *
 * [DESCRIPTION]: Header file for the Application
 *
 * [AUTHOR]: Micheal Onsy
 *
 *******************************************************************************/

#ifndef APP_H_
#define APP_H_
/*******************************************************************************
 *                            Includes                                         *
 *******************************************************************************/
#include <string.h>
#include "../MCAL/I2C/i2c.h"
#include "../MCAL/UART/uart.h"
#include "../HAL/EEPROM/EEPROM.h"
#include "../LIBRARY/common_macros.h"
#include "../LIBRARY/Std_type.h"
#define IDENTICAL 0

/*******************************************************************************
 *                             Functions Prototypes                            *
 *******************************************************************************/

void App_init(void);
void App_Update(void);

#endif /* APP_H_ */
