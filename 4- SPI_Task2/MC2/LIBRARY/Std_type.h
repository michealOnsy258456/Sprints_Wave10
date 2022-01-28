/*
 * Std_type.h
 *
 *  Created on: Jan 19, 2022
 *      Author: Micheal-Onsy
 */

#ifndef LIBRARY_STD_TYPE_H_
#define LIBRARY_STD_TYPE_H_

#include <avr/delay.h>
/*- PRIMITIVE TYPES ----------------------------------------*/
typedef unsigned char uint8_t;               /*                       0 .. 255                        */
typedef signed char sint8_t;                 /*                      -128 .. +127                     */

//typedef unsigned short uint16_t;             /*                        0 .. 65535                     */
typedef signed short sint16_t;               /*                    -32768 .. +32767                   */

//typedef unsigned int uint32_t;               /*                   0 .. 4294967295                     */
typedef signed int sint32_t;                 /*             -2147483648 .. +2147483647                */

typedef unsigned long long uint64_t;         /*                0..18446744073709551615                */
typedef signed long long sint64_t;           /*-9,223,372,036,854,775,808 .. 9,223,372,036,854,775,807*/

typedef float         		float32_t;
typedef double              float64_t;
//typedef void(*Ptr_VoidFuncVoid_t)(void);

/*- MACROS -------------------------------------------------*/
#define NULL_PTR        ((void*)(0))

#define ERROR_OK	0
#define ERROR_NOK   1

/* Boolean Values */

#ifndef FALSE
#define FALSE       (0u)
#endif

#ifndef TRUE
#define TRUE        (1u)
#endif

#define HIGH        (1u)
#define LOW         (0u)

#define STD_HIGH    (1u)   	  /* Standard HIGH */
#define STD_LOW     (0u)	  /* Standard LOW */

#define E_OK        (0u)      /* Function Return OK */
#define E_NOT_OK    (1u)      /* Function Return NOT OK */

#define END_OF_STRING   (uint8_t)('\0')
#define NEW_LINE        (uint8_t)('\r')
#define BACKSPACE       (uint8_t)('\b')

#endif /* LIBRARY_STD_TYPE_H_ */
