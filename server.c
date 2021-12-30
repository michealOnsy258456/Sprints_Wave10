/*
 * Server.c
 *
 *  Created on: Dec 27, 2021
 *      Author: Micheal-Onsy
 */

/*****************************************************************
*                      Includes                                 
*****************************************************************/
#include "server.h"

/* server database */
struct node * head = NULL;

/* server database */
ST_accountBalance_t database[DATABASE_SIZE] =
{		/*primaryAN*/ /*Balance*/
		{100.0,"123456789"},
		{6000.00,"234567891"},
		{3250.25,"567891234"},
		{1500.12,"456789123"},
		{500.00,"258649173"},
		{2100.00,"654823719"},
		{0.00,"971362485"},
		{1.00,"793148625"},
		{10.12,"123123456"},
		{0.5555,"456789321"}
};

/************************************************************************************
 * Variable (in): string containing the PAN.
 * Return value: return index of the PAN from the database.
 * Description: get the balance index from the database.
 ************************************************************************************/
uint8_t get_balance(uint8_t * pan)
{
	uint8_t index = PAN_DOES_NOT_EXIST;

	/* loops the database */
	for (int i = 0; i < DATABASE_SIZE; i++)
	{
		/* check if this index contains the requested PAN */
		if (strcmp(pan, database[i].primaryAccountNumber) == 0)
		{
			index = i;
			break;
		}
	}
	return index;
}
/************************************************************************************
 * Parameters (in): pan_index - index of the PAN in the database.
 *				   amount - amount of the transaction.
 * Description: update the balance of the user in the database.
 ************************************************************************************/
void update_balance(uint8_t index, float amount)
{
	/* decrease the value of balance in the database */
	database[index].balance -= amount;
}
/************************************************************************************
 * Parameters (in):string containing the PAN and amount of the transaction.
 * Return value: transaction_status (CCEPTED_TRANSACTION or DECLINED_TRANSACTION values).
 * Description: check if transaction is valid or not and return the transaction status
 ************************************************************************************/
uint8_t transaction(ST_cardData_t card_data, ST_terminalData_t terminal_data)
{
	/*variable to know the status of the function */
	uint8_t transaction_status;

	/* get the PAN index in the database */
	uint8_t pan_index = get_balance(card_data.primaryAccountNumber);

	if (pan_index == PAN_DOES_NOT_EXIST)
	{
		transaction_status = DECLINED_TRANSACTION;
	}
	else
	{
		/* check if there is enough money in the balance for the transaction */
		if (database[pan_index].balance >= terminal_data.transAmount)
		{
			/* update the balance */
			update_balance(pan_index, terminal_data.transAmount);
			transaction_status = ACCEPTED_TRANSACTION;
		}
		else
		{
			transaction_status = DECLINED_TRANSACTION;
		}
	}
	/* save transaction in server */
	ST_transaction_t transaction_data;

	transaction_data.cardHolderData = card_data;
	transaction_data.transData = terminal_data;
	transaction_data.transStat = ( transaction_status == DECLINED_TRANSACTION? DECLINED:APPROVED);
	save_history (transaction_data);


	/* return the transaction status */
	return transaction_status;
}


/************************************************************************************
 * Parameters (in): struct holding all transaction data.
 * Description: insert the transaction data in it's places.
 ************************************************************************************/
void save_history(ST_transaction_t transaction_data)
{
	/* enter new node on the top of stack */
	struct node * new_node = (struct node *)malloc(sizeof(struct node));
	new_node->next = NULL;
	new_node->data = transaction_data;

	/* if this first transaction need the head to be on the first place of the list*/
	if (head == NULL)
	{
		new_node->next = head;
		head = new_node;
		return;
	}

	struct node * temp_node = head;
	struct node * prev_node = NULL;

	/* loops on transaction  */
	while (temp_node != NULL)
	{
		/* compares pan number. */
		for (int i = 0; i < 20; i++)
		{
			/* if the new node PAN is smaller than the temp node */
			if (new_node->data.cardHolderData.primaryAccountNumber[i] < temp_node->data.cardHolderData.primaryAccountNumber[i])
			{
				/* if temp node is the first node. */
				if (temp_node == head)
				{
					new_node->next = temp_node;
					head = new_node;
					return;
				}
				else
				{
					new_node->next = temp_node;
					prev_node->next = new_node;
					return;
				}
			}
			/* if the new node PAN is bigger than the temp node. */
			else if (new_node->data.cardHolderData.primaryAccountNumber[i] > temp_node->data.cardHolderData.primaryAccountNumber[i])
			{
				/* if that's the last node in history */
				if (temp_node->next == NULL)
				{
					temp_node->next = new_node;
					new_node->next = NULL;
					return;
				}
				else
				{
					break;
				}
			}
		}



		prev_node = temp_node;
		temp_node = temp_node->next;
	}
	/*when the new node has the same primary account number  as the last node in history. */
	if (new_node->next == NULL && prev_node->next == NULL)
	{
		prev_node->next = new_node;
		new_node ->next=NULL;
	}
}
