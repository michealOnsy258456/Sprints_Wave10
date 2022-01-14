/*
 * std_types.h
 *
 *  Created on: Jan 2, 2022
 *      Author: Micheal-Onsy
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/*-------------------TYPE DEFs--------------------------*/
/*UNSIGNED INT*/
typedef unsigned char                   uint8_t;
typedef unsigned short int              uint16;
typedef unsigned long int               uint32_t;
typedef unsigned long long int          uint64_t;
/*SIGNED INT*/
typedef signed char                     int8_t;
typedef signed short int                int16;
typedef signed long int                 int32_t;
typedef signed long long int            int64_t;
/*FLOAT*/
typedef float                           float32_t;
typedef double                          double64_t;

/*POINTER TO FUNCTION (VOID FUNC(VOID))*/
void (*Ptr_VoidFuncVoid_t)(void);
/*ERROR STATE*/
typedef uint8_t ERROR_STATE_t;
/*----------------COMMON MACRROS----------------------*/
#define ERROR_OK        (uint8_t)0
#define ERROR_NOK       (uint8_t)1
#define INIT     (uint8_t)1
#define NOT_INIT (uint8_t)0

#define NULL_PTR        ((void*)(0))
#define NULL_TERMINATOR (uint8_t)('\0')
#define END_OF_STRING   (uint8_t)('\0')
#define NEW_LINE        (uint8_t)('\r')
#define BACKSPACE       (uint8_t)('\b')


#endif /* STD_TYPES_H_ */
