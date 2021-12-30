/*
 * Server.h
 *
 *  Created on: Dec 27, 2021
 *      Author: Micheal-Onsy
 */

#ifndef SERVER_H_
#define SERVER_H_

/*****************************************************************
*                      Includes                                 
*****************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "std_types.h"
//#include "terminal.h"



/*****************************************************************
*                      Standard Data Types                                 
*****************************************************************/

/* card data struct */
typedef struct ST_cardData_t
{
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
} ST_cardData_t;

/* terminal data struct */
typedef struct ST_terminalData_t
{
	float transAmount ;
	float maxTransAmount;
	uint8_t transactionDate[11];
} ST_terminalData_t;

/* transaction status enum */
typedef enum EN_transStat_t
{
	DECLINED,
	APPROVED
} EN_transStat_t;

/* transaction data struct */
typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t transData;
	EN_transStat_t transStat;
} ST_transaction_t;

/* account balance struct */
typedef struct ST_accountBalance_t {
	float balance;
	uint8_t primaryAccountNumber[20];
} ST_accountBalance_t;

/* struct  node */
struct node
{
	struct node * next;
	struct ST_transaction_t data;
}node;

/*****************************************************************
*                      Local Macros
*****************************************************************/
#define DATABASE_SIZE 		 10
#define APPROVED_TRANSACTION  0
#define INSUFFICIENT_BALANC   1
#define PAN_DOES_NOT_EXIST    (DATABASE_SIZE+1)
#define ACCEPTED_TRANSACTION  1
#define DECLINED_TRANSACTION  0

extern ST_accountBalance_t database[DATABASE_SIZE];


/*****************************************************************
 *                      LOCAL FUNCTIONS PROTOTYPES
*****************************************************************/
/* Function to get balance from database. */
uint8_t get_balance(uint8_t * pan);

/* Function to update amount from balance */
void update_balance(uint8_t pan_index, float amount);


/* Function to receive transaction from terminal. */
uint8_t transaction(ST_cardData_t card_data, ST_terminalData_t terminal_data);

/* save transaction history */
void save_history(ST_transaction_t transaction_data);

#endif /* SERVER_H_ */
