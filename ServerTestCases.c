/*
 *  ServerTestCases.c
 *
 *  Created on: Dec 29, 2021
 *  Author: Micheal-Onsy
 */

/*****************************************************************
*                      Includes                                 
*****************************************************************/

#include"ServerTestCases.h"

/************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: test the get_balance.
************************************************************************************/
void GetBalanceTestCases(void)
{
	uint8_t pan_index;

	/* not existing balance */
	printf("Testing senrio 1 :- if the entered pan is not exist: \n");
	pan_index = get_balance("012345");
	if(pan_index == PAN_DOES_NOT_EXIST)
    	printf("Test Case If I Entered Wrong PAN --> PASSED \n");
	else
    	printf("Test Case If I Entered Wrong PAN --> FAILED \n");

	/* existing balance of any index  */
	printf("Testing senrio 2 :- if the entered pan is exist \n");
	pan_index = get_balance("123456789");
	if(pan_index != PAN_DOES_NOT_EXIST)
    	printf("Test Case If I Entered True PAN In Database In First index --> PASSED \n");
	else
    	printf("Test Case If I Entered True PAN In Database In First index --> FAILED \n");
}

/************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: test the transaction.
************************************************************************************/
void TransactionTestCases(void)
{
	uint8_t pan_index;
	uint8_t transaction_status;

	pan_index = get_balance("456789123");

	/* test case 1 */
	printf("Testing senrio 3 :- if the entered pan is exist \n");
	ST_cardData_t test_case_1_card_data = { "Yehia Mohammed", "456789123","12/19" };
	ST_terminalData_t test_case_1_terminal_data = { 20.50, 5000, "27/11/2019" };
	transaction_status = transaction(test_case_1_card_data, test_case_1_terminal_data);
	/* check that the balance is updated after an accepted transaction */
	assert(database[pan_index].balance- 1479.62 < 0.1);
	assert(transaction_status == ACCEPTED_TRANSACTION);
    printf("check that the balance is updated after an accepted transaction\n ");

/* test case 2 */


	/* test case 3 */
	ST_cardData_t test_case_3_card_data = { "Yehia Mohammed", "456789123","12/19" };
	ST_terminalData_t test_case_3_terminal_data = { 2000.00, 5000, "27/11/2019" };
	transaction_status = transaction(test_case_3_card_data, test_case_3_terminal_data);
	/* check that the balance didn't change after a declined transaction */
    printf("check that the balance didn't change after a declined transaction\n");
	assert(database[pan_index].balance - 1479.62 < 01);
	assert(transaction_status == DECLINED_TRANSACTION);

	/* test case 4 */
	ST_cardData_t test_case_4_card_data = { "Yehia Mohammed", "456789124","12/19" };
	ST_terminalData_t test_case_4_terminal_data = { 20.50, 5000, "27/11/2019" };
	transaction_status = transaction(test_case_4_card_data, test_case_4_terminal_data);
    /*check that the PAN didn't Exist*/
    printf("check that the PAN didn't Exist\n");
    assert(transaction_status == DECLINED_TRANSACTION);

	ST_cardData_t test_case_5_card_data = { "Yehia Mohammed", "456789124","12/19" };
	ST_terminalData_t test_case_5_terminal_data = { 20.50, 5000, "27/11/2019" };
	transaction_status = transaction(test_case_5_card_data, test_case_5_terminal_data);
    /*check that the PAN didn't Exist*/
    printf("check that the PAN didn't Exist\n");
    assert(transaction_status == DECLINED_TRANSACTION);
}

