/*
 * StackTestCases.c
 *
 *  Created on: Dec 29, 2021
 *      Author: Micheal-Onsy
 */

/*****************************************************************
*                      Includes
*****************************************************************/
#include "StackTestCases.h"

/************************************************************************************
* Description: check the pull API prints the correct message on empty stack and the
*			   stack size is still 0.
************************************************************************************/
void PullEmptyStack(void)
{
	pop();
	
	assert(strcmp(Check , "Stack is empty, nothing to pop!\n")==0);
	assert(stack_size == 0);
}

/************************************************************************************
* Description: check the printStack API prints the correct message on empty stack and the
*			   stack size is still 0.
************************************************************************************/
void PrintEmptyStack(void)
{
	printStack();
	assert(strcmp(Check, "Stack is empty, nothing to print!\n") == 0);
	//assert(Check =="Stack is empty, nothing to print!\n");
	assert(stack_size == 0);
}

/************************************************************************************
* Description: check the push API stores the data in stack correctly and the
*			   stack size is increased to 1.
************************************************************************************/
void PushToStack(void)
{
	push(5);
	assert(head->data == 5);
	assert(stack_size == 1);
}

/************************************************************************************
* Description: check the pull API returns the data in stack correctly and the
*			   stack size is decreased to 0 after pop.
************************************************************************************/
void PullFromStack(void)
{
	uint8_t pop_value = pop();
	assert(pop_value == 5);
	assert(stack_size == 0);
}

/************************************************************************************
* Description: check the push API prints the correct message when stack is filled 
*			   and checks the stack size is maximum when the message was printed.
************************************************************************************/
void FillStack(void)
{
	for (int i = 1; i <= MAX_STACK_SIZE + 1; i++)
	{
		push(i);
	}
	assert(strcmp(Check, "Stack Overflow will occur, reverting push!\n") == 0);
	assert(stack_size == MAX_STACK_SIZE);
}

/************************************************************************************
* Description: check the printStack API prints all stack and doesn't change the 
*			   stack size, you should see the console to make sure the API printed
*			   from Max stack size to 1.
************************************************************************************/
void TestPrintStack(void)
{
	printStack();
	assert(stack_size == MAX_STACK_SIZE);
}

/************************************************************************************
* Description: check the pull API pops data correctly and the stack size decreases
*			   on each pop.
************************************************************************************/
void PopAllStack(void)
{
	uint8_t pop_value;
	for (int i = MAX_STACK_SIZE; i >= 1; i--)
	{
		pop_value = pop();
		assert(pop_value == i);
		assert(stack_size == i-1);
	}
}
