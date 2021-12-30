/*
 * Stack.c
 *
 *  Created on: Dec 28, 2021
 *      Author: Micheal-Onsy
 */

/*****************************************************************
*                      Includes
*****************************************************************/

#include "Stack.h"

/* define head pointer */
struct node * head = NULL;

/* current stack size */
uint8_t stack_size = 0;

/* string to save check to be printed and can be used in test cases. */
char * Check;

/* global value store current value of stack to be used in unit testing. */
uint8_t stack_size;




/************************************************************************************
* variable (in): u8_data - data to be pushed to stack.
* Description: to push data in the stack
************************************************************************************/
void push(uint8_t u8_data)
{
	/* check if stack if full */
	if (stack_size >= MAX_STACK_SIZE)
	{
		Check= "Stack Overflow will occur, reverting push!\n";
		return;
	}

	/* add new node on the top of stack */
	struct node * new_node = (struct node *)malloc(sizeof(struct node));
	new_node->next = head;
	new_node->data = u8_data;


	/* make head point to the new node */
	head = new_node;

	/* increment stack size*/
	stack_size++;
}
/************************************************************************************
* Return : value on top of the stack
* Description: Pops the data on top of stack and decrement stack size by 1.
************************************************************************************/
uint8_t pop()
{
	uint8_t value;

	/* check if stack if empty */
	if (stack_size == EMPTY_STACK)
	{
		Check="Stack is empty, nothing to pop!\n";
		return -1;
	}

	/* copy top node on stack to local variable */
	struct node * temp_node = head;

	/* get value from the top node */
	value = temp_node->data;

	/* head point to the next node */
	head = temp_node->next;

	/* free the temp for the top node */
	free(temp_node);

	/* decrement stack size */
	stack_size--;

	/* return value that was on the top node. */
	return value;
}

/************************************************************************************
* Description: prints all the stack data
************************************************************************************/
void printStack()
{
	/*local variable*/
	struct node * temp_node = head;

	/* check if stack is empty */
	if (head == NULL)
	{
		Check="Stack is empty, nothing to print!\n";
	}

	/* print all stack data */
	while (temp_node != NULL)
	{
		printf("%d\n", temp_node->data);
		temp_node = temp_node->next;
	}
}
/************************************************************************************
* Description: full all the stack
************************************************************************************/

void FillAllStack(void)
{
	/*algorithm*/
	for (int i = 1; i <= 100; i++)
	{
		push(i);
	}

}
