 /******************************************************************************
 *
 * Module: DIO
 *
 * File Name: DIO.h
 *
 * Description: Header file for the DIO AVR driver
 *
 * Author: Micheal Onsy
 *
 *******************************************************************************/


#ifndef DIO_H_
#define DIO_H_
/*******************************************************************************
 *                            Includes                                         *
 *******************************************************************************/

#include "../../LIBRARY/Std_type.h"
#include "../../LIBRARY/common_macros.h"
#include "../../LIBRARY/Register.h"

/*******************************************************************************
 *                            Data type                                  *
 *******************************************************************************/


typedef enum
{
	E_DIO_SUCCESS,
	E_DIO_INVALID_PORT_NUMBER,
	E_DIO_INVALID_PIN_DIRECTION,
	E_DIO_SET_TO_NON_INPUT

}ERROR_STATE_t;

/*******************************************************************************
 *                            Common MACROS                                     *
 *******************************************************************************/


/* Macros for PORTS */
#define PORTa             0
#define PORTb             1
#define PORTc             2
#define PORTd             3

/* Macros for PINS */
#define PIN0              0
#define PIN1              1
#define PIN2              2
#define PIN3              3
#define PIN4              4
#define PIN5              5
#define PIN6              6
#define PIN7              7

/* Macros for Pin Direction */
#define DIO_u8_OUTPUT            255
#define DIO_u8_INPUT             0

/* Macros for Pin Value */
#define DIO_u8_HIGH              1
#define DIO_u8_LOW               0

void DIO_voidInit         (void);
/*-----------FUNCTION DECLERATIONS-------------*/
/*******************************************************************************
 *                           FUNCTION DECLERATIONS                                        *
 *******************************************************************************/

ERROR_STATE_t DIO_setPortDirection(uint8_t PORTID, uint8_t PortDirection);
ERROR_STATE_t DIO_setPinDirection(uint8_t PortID , uint8_t PinNumber, uint8_t PinDirection);
ERROR_STATE_t DIO_writePortValue(uint8_t PortID, uint8_t PortValue);
ERROR_STATE_t DIO_writePinValue(uint8_t PortID, uint8_t PinNumber,uint8_t PinDirection);
ERROR_STATE_t DIO_readPort(uint8_t PortID, uint8_t* PortState);
ERROR_STATE_t DIO_readPin(uint8_t PortID,uint8_t PinNumber, uint8_t* PinState);
ERROR_STATE_t DIO_TogglePin(uint8_t PortID, uint8_t PinNumber);
ERROR_STATE_t DIO_SetPullupRes(uint8_t PortID, uint8_t PinNumber);


#endif /* DIO_H_ */
