 /******************************************************************************
 *
 * [MODULE]: KEYPAD
 *
 * [FILE NAME]: keypad.h
 *
 * [DESCRIPTION]: Header file for the Keypad driver
 *
 * [AUTHOR]: Micheal Onsy
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../../LIBRARY/std_types.h"
#include "../../LIBRARY/Macros.h"

#include "../../MCAL/DIO/dio.h"
#include "../../MCAL/TIMER/timer.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define N_col 3
#define N_row 4

/* Keypad Port Configurations */
#define KEYPAD_PORT		PORTa
#define KEYPAD_COL_PIN	PIN4
#define KEYPAD_ROW_PIN	PIN0

/* Keypad configurations for state machine */
#define PRESSED         (1u)
#define NOT_PRESSED     (0u)
#define DEBOUNCING      (2u)
#define Operation_Success 200
#define INITIAL_VALUE	(0u)
#define TWENTY_MS		(20000u)

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*******************************************************************************
* Service Name: KEYPAD_Init
* Service ID[hex]: 0x10
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): void
* Parameters (in/out): None
* Parameters (out): None
* Return value: Std_ReturnType
* Description: Function to Initialize the KEYPAD
********************************************************************************/
ERROR_STATE_t KEYPAD_Init(void);

/*******************************************************************************
* Service Name: KEYPAD_getStatus
* Service ID[hex]: 0x20
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): au8_data
* Parameters (in/out): None
* Parameters (out): None
* Return value: Std_ReturnType
* Description: Function responsible for getting the status of the KEYPAD
********************************************************************************/
ERROR_STATE_t KEYPAD_getStatus(uint8_t * data);
uint8_t data_return(void);

#endif /* KEYPAD_H_ */
