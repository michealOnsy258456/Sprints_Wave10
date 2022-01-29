/******************************************************************************
 *
 * [MODULE]: SPI
 *
 * [FILE NAME]: SPI.c
 *
 * [DESCRIPTION]: Source file for the SPI
 *
 * [AUTHOR]: Micheal Onsy
 *
 *******************************************************************************/

#include "SPI.h"

/*******************************************************************************
 *                              LOCAL MACRO                                   *
 *******************************************************************************/

/* SPCR */
#define SPIE     7
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
/**
 * @brief: This function initialize the SPI pins as master.
 *
 * @return function void.
 *
 */
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
/**
 * @brief: This function initialize the SPI pins as Slave.
 *
 * @return function void.
 *
 */
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
/**
 * @brief: This function puts a character in the SPI buffer.
 *
 * @param [in]  data      -  character to be send through UART.
 *
 * @return function void.
 */
void SPI_sendByte(const uint8_t data)
{
	SPDR = data; //send data by SPI
	while(BIT_IS_CLEAR(SPSR,SPIF)){} //wait until SPI interrupt flag=1 (data is sent correctly)
}
/**
 * @brief: This function receive a character in the SPI buffer.
 *
 * @param [in]  a_Data      -  character to be send through UART.
 *
 * @return function error state.
 */
uint8_t SPI_recieveByte(void)
{
   while(BIT_IS_CLEAR(SPSR,SPIF)){} //wait until SPI interrupt flag=1(data is receive correctly)
   return SPDR; //return the received byte from SPI data register
}
/**
 * @brief: This function sends a string through SPI.
 *
 * @param [in]  Str    -  pointer to string to send through SPI.
 *
 * @return function void.
 */
void SPI_SendString(const uint8_t *Str)
{
	uint8_t i = 0;
	while(Str[i] != '\0')
	{
		SPI_sendByte(Str[i]);
		i++;
	}
}
/**
 * @brief: This function receive a string through spi.
 *
 * @param [out] Str    -  pointer to string to save the string through SPI.
 *
 * @return function error state.
 */
void SPI_ReceiveString(uint8_t *Str)
{
	uint8_t i = 0;
	Str[i] = SPI_recieveByte();
	while(Str[i] != NEW_LINE)
	{
		i++;
		Str[i] = SPI_recieveByte();
	}
	Str[i] = '\0';
}