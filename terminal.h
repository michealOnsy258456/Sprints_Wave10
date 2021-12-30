/*
 * Terminal.h
 *
 *  Created on: Dec 27, 2021
 *      Author: Micheal-Onsy
 */

#ifndef TERMINAL_H_
#define TERMINAL_H_

/*****************************************************************
*                      Includes                                 
*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "std_types.h"
#include "server.h"

/*****************************************************************
*                      Local Macros
*****************************************************************/
#define NOT_EXPIRED 			1
#define EXPIRED 				0
#define VALID_AMOUNT 			1
#define INVALID_AMOUNT 			0
#define MAXIMUM_ALLOWED_AMOUNT 	5000.0


/*****************************************************************
 *                      LOCAL FUNCTIONS PROTOTYPES
*****************************************************************/
/* Function to check if transaction amount is valid */
uint8_t check_expired(ST_cardData_t card_data, ST_terminalData_t terminal_data);

/* Function to check if transaction amount is valid */
uint8_t check_amount(ST_terminalData_t terminal_data);

/* Function to send transaction data to server. */
uint8_t send_Data(ST_cardData_t card_data, ST_terminalData_t terminal_data);


#endif /* TERMINAL_H_ */
