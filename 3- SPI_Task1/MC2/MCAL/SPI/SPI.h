/******************************************************************************
 *
 * [MODULE]: SPI
 *
 * [FILE NAME]: SPI.h
 *
 * [DESCRIPTION]: Header file for the SPI
 *
 * [AUTHOR]: Micheal Onsy
 *
 *******************************************************************************/
#ifndef MCAL_SPI_SPI_H_
#define MCAL_SPI_SPI_H_


/*******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/

#include "../../LIBRARY/Std_type.h"
#include "../../LIBRARY/common_macros.h"
#include "../../LIBRARY/Register.h"
#include "../../MCAL/DIO/DIO.h"
/*******************************************************************************
 *                      Functions Prototypes                                   *
 ******************************************************************************/

void SPI_initMaster(void);
void SPI_initSlave(void);
void SPI_sendByte(const uint8_t data);
uint8_t SPI_recieveByte(void);
void SPI_sendString(const uint8_t *Str);
void SPI_receiveString(uint8_t *Str);


#endif /* MCAL_SPI_SPI_H_ */
