/*
 * SPI.h
 *
 *  Created on: Jan 24, 2022
 *      Author: Micheal-Onsy
 */

#ifndef MCAL_SPI_SPI_H_
#define MCAL_SPI_SPI_H_


#include "Std_type.h"
#include "common_macros.h"
#include "Register.h"
#include "DIO.h"
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void SPI_initMaster(void);
void SPI_initSlave(void);
void SPI_sendByte(const uint8_t data);
uint8_t SPI_recieveByte(void);
void SPI_sendString(const uint8_t *Str);
void SPI_receiveString(uint8_t *Str);


#endif /* MCAL_SPI_SPI_H_ */
