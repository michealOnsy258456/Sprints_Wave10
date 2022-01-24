/*
 * KEYPAD.h
 *
 *  Created on: Jan 17, 2022
 *      Author: Micheal-Onsy
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "Register.h"
#include "common_macros.h"
#include "Std_type.h"


/*- PRIMITIVE TYPES ----------------------------------------*/
typedef uint8_t KEYPAD_ERROR_state_t;
/*- ERRORS DEFINITIONS--------------------------------------*/
/**
* @brief: This return value indicate that the function
* ran successfully and it returns no errors.
*/
#define           E_KEYPAD_SUCCESS                    (KEYPAD_ERROR_state_t)( 0 )
/**
* @brief: This return value indicate that a function got an
* uninitialized pointer.
*/
#define           E_KEYPAD_NULL_PTR                   (KEYPAD_ERROR_state_t)( 1 )
/**
* @brief: This return value indicate that a function got an
* invalid channel.
*/
#define           E_KEYPAD_INVALID_CH                 (KEYPAD_ERROR_state_t)( 2 )


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define N_col 3
#define N_row 5

/* Keypad Port Configurations */
#define KEYPAD_PORT_OUT PORTC
#define KEYPAD_PORT_IN  PINC
#define KEYPAD_PORT_DIR DDRC

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* 
 * Description: Function responsible for getting the pressed keypad key 
 */
KEYPAD_ERROR_state_t  KeyPad_getPressedKey(uint8_t *a_Value);

#endif /* KEYPAD_H_ */
