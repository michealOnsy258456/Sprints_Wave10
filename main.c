/*
 * main.c
 *
 *  Created on: Dec 27, 2021
 *      Author: Micheal-Onsy
 */
/*****************************************************************
*                      Includes                                 
*****************************************************************/
#include <stdio.h>
#include "std_types.h"
#include "terminal.h"


/*****************************************************************
*                      Local Macros
*****************************************************************/

#define __SERVER_TEST_CASES__ 0
#define __TERMINAL_TEST_CASES__ 0

#if(__SERVER_TEST_CASES__==1)
#include "ServerTestCases.h"
int main(void)
{
	/* run all test cases */
	GetBalanceTestCases();
	TransactionTestCases();

	/* if no assertion error happened, print all tests passed message. */
	printf("All test cases passed successfully! :))\n");
	return 1;
}
#elif(__TERMINAL_TEST_CASES__==1)
#include "TerminalTestCases.h"

int main(void)
{
	/* run all test cases */
	CheckExpiredTestCases();
	CheckAmountTestCases();
	SendTestCases();

	/* if no assertion error happened, print all tests passed message. */
	printf("All test cases passed successfully! :))\n");
	return 1 ;
}


#else

extern struct node * head;

/* vairable to store terminala data */
ST_terminalData_t terminal_data ={0.0,0.0,{0}};
/* variable to store card data */
ST_cardData_t card_data ={{0},{0},{0}};
int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);


	uint8_t Transaction_counter = 1;
	/* variable to store server response */
	uint8_t user_response = 0;
	/* variable used in counter loop */
	uint8_t Counter_Loop = 0;
	/* variable to store server response */
	uint8_t server_response = 0;
	/* a dummy character variable used to clear stdin buffer */
	uint8_t dummy_data = 0;
	/* initialize maximum allowed transaction amount */
	terminal_data.maxTransAmount = MAXIMUM_ALLOWED_AMOUNT;

	while (1)
	{

		user_response = 0;
		printf("Please Enter Card Data: \n");
		printf("Please Enter the Card Holder Name : \n");

		/* store card holder name in card data */
		for(Counter_Loop = 0 ; ( (dummy_data = getchar()) != '\n' ) ; Counter_Loop++)
		{
			card_data.cardHolderName[Counter_Loop] = dummy_data;
		}
		card_data.cardHolderName[Counter_Loop] = '\0';

		/* to make dummy data to zero again */
		dummy_data = 0;

		printf("Please Enter the Primary Account Number: \n");

		/* store PAN in card data */
		for(Counter_Loop = 0 ; ( (dummy_data = getchar()) != '\n' ) ; Counter_Loop++)
		{
			card_data.primaryAccountNumber[Counter_Loop] = dummy_data;
		}
		card_data.primaryAccountNumber[Counter_Loop] = '\0';

		/* to make dummy data to zero again */
		dummy_data = 0;

		printf("Please enter card Expiry Date: \n");

		/* store card expiration date in card data */
		for(Counter_Loop = 0 ; ( (dummy_data = getchar()) != '\n' ) ; Counter_Loop++)
		{
			card_data.cardExpirationDate[Counter_Loop] = dummy_data;
		}
		card_data.cardExpirationDate[Counter_Loop] = '\0';

		/* to make dummy data to zero again */
		dummy_data = 0;

		printf("Please Enter Terminal Data: \n");
		printf("Please Enter the transaction Amount: \n");

		/* store transaction amount in terminal data */
		scanf("%f",&terminal_data.transAmount);
		getchar() ;

		/* check if invalid amount is entered */
		if (check_amount(terminal_data) == INVALID_AMOUNT)
		{
			printf("The Transaction is DECLINED \n");
			printf("welcome\n");
		}
		else
		{
			printf("Please Enter transaction Date: \n");

			/* store transaction in terminal data */
			for(Counter_Loop = 0 ; ( (dummy_data = getchar()) != '\n' ) ; Counter_Loop++)
			{
				terminal_data.transactionDate[Counter_Loop] = dummy_data;
			}
			terminal_data.transactionDate[Counter_Loop] = '\0';

			/* to make dummy data to zero again */
			dummy_data = 0;

			/* check if card is expired */
			if (check_expired(card_data, terminal_data) == EXPIRED)
			{
				printf("The Transaction is DECLINED \n");
			}
			else
			{

				/* send card and terminal data to server */
				server_response = send_Data(card_data, terminal_data);

				/* check if transaction in successful */
				if (server_response == ACCEPTED_TRANSACTION)
				{
					printf("The Transaction is APPROVED. \n");
				}
				else if (server_response == DECLINED_TRANSACTION)
				{
					printf("The Transaction is DECLINED \n");
				}
				else
				{
				}
			}
		}

		printf("Do you want to continue (y/n)?: \n");

		/* get user response */
		user_response = getchar();
		getchar();
		/* check if user wants to make another transaction or not */
		if (user_response == 'y' || user_response == 'Y')
		{
			/* do not make any thing */
		}
		else if (user_response == 'n' || user_response == 'N')
		{
			break;
		}
		else
		{
			break;
		}
	}


	/* print transaction history when the user finish the program. */
		printf("Save Transaction section: \n \n");
		struct node * temp_node = head;

		/* loops on transaction history nodes */
		while (temp_node != NULL)
		{
			printf("%d  \n", Transaction_counter);
			printf("card data:\n  Card Holder Name: %s \n  ",temp_node->data.cardHolderData.cardHolderName);
			printf("  PAN: %s \n",temp_node->data.cardHolderData.primaryAccountNumber);
			printf("  Expiration Date:%s \n",temp_node->data.cardHolderData.cardExpirationDate);

			printf("terminal data:\n  Transaction Amount: %f \n",temp_node->data.transData.transAmount );
			printf("  Max Allowed From Terminal: %f \n",temp_node->data.transData.maxTransAmount );
			printf("  Transaction Date: %s \n",temp_node->data.transData.transactionDate );


			printf("  status: %s \n", temp_node->data.transStat == APPROVED? "Approved": "Declined");

			printf("------------------------------------------\n\n");

			Transaction_counter++;

			temp_node = temp_node->next;
		}

	printf("!!!Finish!!!!");
	return 1;
}

#endif
