/******************************************************************************
 *
 * [MODULE]: UART
 *
 * [FILE NAME]: UART.c
 *
 * [DESCRIPTION]: Source file for the UART
 *
 * [AUTHOR]: Micheal Onsy
 *
 *******************************************************************************/
/*******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/
#include "UART.h"


/* UCSRA */
#define RXC     7
#define TXC     6
#define UDRE    5
#define FE      4
#define DOR     3
#define PE      2
#define U2X     1
#define MPCM    0

/* UCSRB */
#define RXCIE   7
#define TXCIE   6
#define UDRIE   5
#define RXEN    4
#define TXEN    3
#define UCSZ2   2
#define RXB8    1
#define TXB8    0

/* UCSRC */
#define URSEL   7
#define UMSEL   6
#define UPM1    5
#define UPM0    4
#define USBS    3
#define UCSZ1   2
#define UCSZ0   1
#define UCPOL   0


/**
 * @brief: This function initialize the UART pin.
 *
 * @return function error state.
 *
 */
UART_ERROR_state_t  UART_VidInit(UART_Config *a_ptr,uint16_t a_BoudRate)
{
	if(NULL_PTR == a_ptr)
	{
		return E_UART_NULL_PTR;
	}
	/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = 0 For 8-bit data mode
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/
	// Enable Transmit
	SET_BIT(UCSRB,TXEN);
	//Enable Receive
	SET_BIT(UCSRB,RXEN);
	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * UPM1:0  = 00 Disable parity bit
	 * USBS    = 0 One stop bit
	 * UCSZ1:0 = 11 For 8-bit data mode
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/
	UCSRC = (1<<URSEL); //To Write in Register UCSRC

	if (a_ptr->Mode==UART_AsyncDouble)
	{
		UCSRA |=  (1<<U2X);
		UCSRC=(UCSRC & 0xF9)|(((a_ptr->DataSize) & 0x03)<<UCSZ0);
		UCSRB=(UCSRB & 0xFB)|(((a_ptr->DataSize) & 0x04)<<UCSZ1);
	}

	if (a_ptr->Mode != UART_Sync)
	{
		//parity
		UCSRC=(UCSRC & 0xCF)|((a_ptr->Parity)<<UPM0);
		//StopBit
		UCSRC|=(a_ptr->StopBit)<<USBS;
		// Character Size
		UCSRC=(UCSRC & 0xF9)|(((a_ptr->DataSize) & 0x03)<<UCSZ0);
		UCSRB=(UCSRB & 0xFB)|(((a_ptr->DataSize) & 0x04)<<UCSZ2);
	}
	//BoudRate
	if (a_ptr->Mode == UART_AsyncNormal)
	{
		a_BoudRate= (((F_CPU / (a_BoudRate * 16UL))) - 1);
	}
	else if (a_ptr->Mode == UART_AsyncDouble)
	{
		a_BoudRate= (((F_CPU / (a_BoudRate * 8UL))) - 1);
	}
	else if (a_ptr->Mode == UART_Sync)
	{
		a_BoudRate= ((float32_t)F_CPU/(2*a_BoudRate))-1;
	}
	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRL=a_BoudRate;
	UBRRH=(a_BoudRate>>8);


	return E_UART_SUCCESS;
}
/**
 * @brief: This function receive a character f the UART buffer.
 *
 * @param [in]  a_Data      -  character to be send through UART.
 *
 * @return function error state.
 */
uint8_t UART_recieveByte(void)
{

	/* RXC flag is set when the UART receive data so wait until this
	 * flag is set to one */
	while(!(UCSRA & (1<<RXC)));
	/* Read the received data from the Rx buffer (UDR) and the RXC flag
	   will be cleared after read this data */
	return UDR;
}
/**
 * @brief: This function puts a character in the UART buffer.
 *
 * @param [in]  a_Data      -  character to be send through UART.
 *
 * @return function error state.
 */
UART_ERROR_state_t UART_sendByte(const uint8_t a_Data)
{

	/* Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now */
	UDR=a_Data;
	/* UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one */
	while(!(UCSRA & (1<<UDRE)));

	return E_UART_SUCCESS;

}

/**
 * @brief: This function sends a string through UART.
 *
 * @param [in]  Str    -  pointer to string to send through UART.
 *
 * @return function error state.
 */
UART_ERROR_state_t  UART_sendString(const uint8_t *Str)
{
	/* making sure an initialized pointer is sent to the function */

	if(NULL_PTR == Str)
	{
		return E_UART_NULL_PTR;
	}
	uint8_t i = 0;
	/* keeps sending data until it finds an end of string character in the string */

	while(Str[i] != '\0')
	{
		/* Put data into Str, sends the data */
		UART_sendByte(Str[i]);
		i++;
	}
	/* return success status */
	return E_UART_SUCCESS;
}
/**
 * @brief: This function sends a string through UART.
 *
 * @param [out] Str    -  pointer to string to save the string through UART.
 *
 * @return function error state.
 */
UART_ERROR_state_t  UART_receiveString(uint8_t *Str)
{

	/* making sure an initialized pointer is sent to the function */
	if(NULL_PTR == Str)
	{
		return E_UART_NULL_PTR;
	}
	uint8_t i = 0;
	/* Wait for data to be received it */
	Str[i] = UART_recieveByte();
	while(Str[i] != NEW_LINE)
	{
		i++;
		/* Wait for data to be received it */
		Str[i] = UART_recieveByte();
	}
	Str[i] = '\0';

	/* return success status */
	return E_UART_SUCCESS;
}
