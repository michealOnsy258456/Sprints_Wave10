/*
 * Terminal.c
 *
 *  Created on: Dec 27, 2021
 *      Author: Micheal-Onsy
 */

/*****************************************************************
*                      Includes                                 
*****************************************************************/

#include "terminal.h"

/************************************************************************************
* Parameters (in): card_data - struct holding card data. terminal_data - struct holding terminal data
* Return value: holds EXPIRED or NOT_EXPIRED values.
* Description: check if an entered card is expired.
************************************************************************************/
uint8_t check_expired(ST_cardData_t card_data, ST_terminalData_t terminal_data)
{
	/* variable to store the card date is expired or not */
	uint8_t is_expired;

	/* check if year is the same. */
	if (
		card_data.cardExpirationDate[3] == terminal_data.transactionDate[8] &&
		card_data.cardExpirationDate[4] == terminal_data.transactionDate[9]
		)
	{
		/* if the expire month is bigger than the transaction month */
		if (
			card_data.cardExpirationDate[0] == terminal_data.transactionDate[3] &&
			card_data.cardExpirationDate[1] >= terminal_data.transactionDate[4]
			)
		{
			is_expired = NOT_EXPIRED;
		}
		/* if the expire month is bigger than the transaction month */
		else if (card_data.cardExpirationDate[0] > terminal_data.transactionDate[3])
		{
			is_expired = NOT_EXPIRED;
		}
		else
		{
			is_expired = EXPIRED;
		}
	}
	/* if the expire year is bigger than the transaction year */
	else if (
		card_data.cardExpirationDate[3] == terminal_data.transactionDate[8] &&
		card_data.cardExpirationDate[4] > terminal_data.transactionDate[9]
		)
	{
		is_expired = NOT_EXPIRED;
	}
	/* if the expire year is bigger than the transaction year */
	else if(card_data.cardExpirationDate[3] > terminal_data.transactionDate[8])
	{
		is_expired = NOT_EXPIRED;
	}
	else
	{
		is_expired = EXPIRED;
	}


	/* returns is_expired value */
	return is_expired;
}

/************************************************************************************
* Parameters (in):  struct holding terminal data.
* Return value: is_valid - holds VALID_AMOUNT or INVALID_AMOUNT values.
* Description: check if transaction amount is valid.
************************************************************************************/
uint8_t check_amount(ST_terminalData_t terminal_data)
{

	/* variable to store the transaction amount is valid or not. */
 	uint8_t is_valid;

	/* check  transaction amount is bigger than the maximum amount allowed */
	if (terminal_data.transAmount > terminal_data.maxTransAmount )
	{
		is_valid = INVALID_AMOUNT;
	}
	else
	{
		is_valid = VALID_AMOUNT;
	}

	/* return status value */
	return is_valid;
}


/************************************************************************************
* Parameters (in): struct holding card data.
*				   struct holding terminal data
* Return value:  holds ACCEPTED_TRANSACTION or DECLINED_TRANSACTION values.
* Description: sends pan number and amount to server and returns the server reposne.
************************************************************************************/
uint8_t send_Data(ST_cardData_t card_data, ST_terminalData_t terminal_data)
{
	/* variable to store the transaction status is valid or not. */
	uint8_t transaction_status;

	/* sends the transaction to the server */
	transaction_status = transaction(card_data, terminal_data);

	/* return the transaction status o*/
	return transaction_status;
}
