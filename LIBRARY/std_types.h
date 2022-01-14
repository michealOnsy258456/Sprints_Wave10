/*
 * std_types.h
 *
 *  Created on: Jan 2, 2022
 *      Author: Micheal-Onsy
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_


/* Boolean Data Type */
typedef unsigned char bool;


/* Boolean Values */
#ifndef FALSE
#define FALSE       (0u)
#endif
#ifndef TRUE
#define TRUE        (1u)
#endif

#define HIGH        (1u)
#define LOW         (0u)

/*PLEASE READ THIS*/


/* I Used Util of delay and  uintN_t used in the util also
 * then I comments all data Types for me because do not make any conflict  */


//typedef unsigned char         uint8_t;          /*           0 .. 255             */
//typedef signed char           sint8_t;          /*        -128 .. +127            */
//typedef unsigned short        uint16_t;         /*           0 .. 65535           */
//typedef signed short          sint16_t;         /*      -32768 .. +32767          */
//typedef unsigned long         uint32_t;         /*           0 .. 4294967295      */
//typedef signed long           sint32_t;         /* -2147483648 .. +2147483647     */
//typedef unsigned long long    uint64_t;         /*       0..18446744073709551615  */
//typedef signed long long      sint64_t;
//typedef float                 float32_t;
//typedef double                float64_t;




/*----------------COMMON MACRROS----------------------*/
#define ERROR_OK	0
#define ERROR_NOK   1
#define INIT		1
#define NOT_INIT	0

#define NULL_PTR        ((void*)(0))
#define NULL 	('\0')

#endif /* STD_TYPES_H_ */
