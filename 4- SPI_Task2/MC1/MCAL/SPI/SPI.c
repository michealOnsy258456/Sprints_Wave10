/*
 * SPI.c
 *
 *  Created on: Jan 24, 2022
 *      Author: Micheal-Onsy
 */

#include "SPI.h"
//#include <avr/io.h>

/* SPCR */
#define SPIE    7
#define SPE     6
#define DORD    5
#define MSTR    4
#define CPOL    3
#define CPHA    2
#define SPR1    1
#define SPR0    0


/* SPSR */
#define SPIF    7
#define WCOL    6
/* bits 5-1 reserved */
#define SPI2X   0

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void SPI_initMaster(void)
{
	/******** Configure SPI Master Pins *********
	 * SS(PB4)   --> Output
	 * MOSI(PB5) --> Output
	 * MISO(PB6) --> Input
	 * SCK(PB7) --> Output
	 ********************************************/
	DDRB = DDRB | (1<<PIN4);
	DDRB = DDRB | (1<<PIN5);
	DDRB = DDRB & ~(1<<PIN6);
	DDRB = DDRB | (1<<PIN7);

	SPCR = (1<<SPE) | (1<<MSTR); // enable SPI + enable Master + choose SPI clock = Fosc/4
}

void SPI_initSlave(void)
{
	/******** Configure SPI Slave Pins *********
	 * SS(PB4)   --> Input
	 * MOSI(PB5) --> Input
	 * MISO(PB6) --> Output
	 * SCK(PB7) --> Input
	 ********************************************/
	DDRB = DDRB & (~(1<<PIN4));
	DDRB = DDRB & (~(1<<PIN5));
	DDRB = DDRB | (1<<PIN6);
	DDRB = DDRB & (~(1<<PIN7));

	SPCR = (1<<SPE); // just enable SPI + choose SPI clock = Fosc/4
}

void SPI_sendByte(const uint8_t data)
{
	SPDR = data; //send data by SPI
	while(BIT_IS_CLEAR(SPSR,SPIF)){} //wait until SPI interrupt flag=1 (data is sent correctly)
}

uint8_t SPI_recieveByte(void)
{
   while(BIT_IS_CLEAR(SPSR,SPIF)){} //wait until SPI interrupt flag=1(data is receive correctly)
   return SPDR; //return the received byte from SPI data register
}

void SPI_sendString(const uint8_t *Str)
{
	uint8_t i = 0;
	while(1)
	{
		SPI_sendByte(Str[i]);
		if(Str[i] == '\0')
			return;
		i++;
	}
}
void SPI_ReceiveString(uint8_t *Str)
{
	uint8_t i = 0;
	//Str[i] = SPI_recieveByte();
	while(Str[i] != NEW_LINE)
	{
		i++;
		Str[i] = SPI_recieveByte();
		if( (Str[i] == '\0'))
			return ;
	}
	Str[++i] = '\0';
}
