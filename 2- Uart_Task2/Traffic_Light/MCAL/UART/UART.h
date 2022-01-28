/*
 * UART.h
 *
 *  Created on: Jan 14, 2020
 *      Author: micheal_onsy
 */

#ifndef UART_H_
#define UART_H_
#include "Std_type.h"
#include "common_macros.h"
#include "Register.h"


//stop bit
typedef enum {
	UART_1StopBit,UART_2StopBit
}UART_StopBit;

// data size
typedef enum {
	UART_5Bit,UART_6Bit,UART_7Bit,UART_8Bit,UART_9Bit=7
}UART_DataSize;

//mode syn or asyn
//0 asyn
//1 syn
typedef enum {
	UART_AsyncNormal,UART_AsyncDouble,UART_Sync
}UART_Mode;

//clock
typedef enum {
	UART_RisingTxD_FallingRxD,UART_RisingRxD_FallingTxD
}UART_ClockPolar;

//parity
typedef enum {
	UART_Disable,Reserved,UART_EvenPar,UART_OddPar
}UART_Parity;


typedef struct{
	UART_StopBit	StopBit;
	UART_DataSize	DataSize;
	UART_Mode		Mode;
	UART_Parity		Parity;


}UART_Config;


/*- PRIMITIVE TYPES ----------------------------------------*/
typedef uint8_t UART_ERROR_state_t;

/*- ERRORS DEFINITIONS--------------------------------------*/

/**
* @brief: This return value indicate that the function
* ran successfully and it returns no errors.
*/
#define           E_UART_SUCCESS             (UART_ERROR_state_t)( 0 )

/**
* @brief: This return value indicate that the receive function
* got a frame error.
*/
#define           E_UART_FRAME_ERROR         (UART_ERROR_state_t)( 1 )

/**
* @brief: This return value indicate that the receive function
* got a parity error.
*/
#define           E_UART_PARITY_ERROR        (UART_ERROR_state_t)( 2 )
/**
* @brief: This return value indicate that the receive function
* got an over run error.
*/
#define           E_OVER_RUN_ERROR           (UART_ERROR_state_t)( 3 )
/**
* @brief: This return value indicate that a function
* got an uninitialized pointer.
*/
#define           E_UART_NULL_PTR            (UART_ERROR_state_t)( 4 )
/**
* @brief: This return value indicate that the init function
* got invalid baud rate value.
*/
#define           E_UART_INVALID_BAUD_RATE   (UART_ERROR_state_t)( 5 )
/**
* @brief: This return value indicate that a function
* got invalid channel number.
*/
#define           E_UART_INVALID_CH          (UART_ERROR_state_t)( 6 )
/**
* @brief: This return value indicate that a function
* got invalid interrupt type.
*/
#define           E_UART_INVALID_INT_TYPE    (UART_ERROR_state_t)( 7 )

/*Prototype */
UART_ERROR_state_t UART_VidInit(UART_Config *a_ptr,uint16_t a_BoudRate);
uint8_t UART_recieveByte(void);
UART_ERROR_state_t UART_sendByte(const uint8_t a_Data);
UART_ERROR_state_t UART_sendString(const uint8_t *Str);
UART_ERROR_state_t UART_receiveString(uint8_t *Str);

#endif /* UART_H_ */