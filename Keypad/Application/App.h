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

#include "../HAL/KEYPAD/keypad.h"
#include "../LIBRARY/Macros.h"
#include "../LIBRARY/std_types.h"
#include "../MCAL/DIO/DIO.h"
#include "../MCAL/TIMER/Timer.h"
#include "../HAL/LCD/LCD.h"

/*******************************************************************************
 *                             Functions Prototypes                            *
 *******************************************************************************/

/*******************************************************************************
 * [Function Name]: App_init
 *
 * [Description]: 	Function to Initialize the application to test LCD
 *
 * [Args]:			None
 *
 * [in]			  	None
 *
 * [out]		  	None
 *
 * [in/out]		 	None
 *
 * [Returns]:       None
 *******************************************************************************/
void App_init(void);

/*******************************************************************************
 * [Function Name]: App_Update
 *
 * [Description]: 	Function to update the state of the application
 *
 * [Args]:			None
 *
 * [in]			  	None
 *
 * [out]		  	None
 *
 * [in/out]		 	None
 *
 * [Returns]:       None
 *******************************************************************************/
void App_Update(void);
/*******************************************************************************
 * [Function Name]: App_init_Without_Looping
 *
 * [Description]: 	Function to Initialize the application to test keypad
 *
 * [Args]:			None
 *
 * [in]			  	None
 *
 * [out]		  	None
 *
 * [in/out]		 	None
 *
 * [Returns]:       None
 *******************************************************************************/
void App_init_Without_Looping(void);
#endif /* APP_H_ */
