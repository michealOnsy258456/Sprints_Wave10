/*
 * main.c
 *
 *  Created on: Dec 28, 2021
 *      Author: Micheal-Onsy
 */

#include <stdio.h>
#include "std_types.h"
#include "conio.h"
#include "balanced_parentheses.h"
#include "StackTestCases.h"
#include "BalancedTestCases.h"

#define __STACK_TEST_CASES__ 0
#define __BALANCED_PARENTHESES__ 0



#if (__STACK_TEST_CASES__ == 1)
int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	/* malloc console output to be able to realloc in stack APIs */
	Check = (char*)malloc(sizeof(char));

	/* test cases should be run in the excat order as they depend on each other. */
	PullEmptyStack();
	PrintEmptyStack();
	PushToStack();
	PullFromStack();
	FillStack();
	TestPrintStack();
	PopAllStack();
	/* if no assertion error happened, print all tests passed message. */
	printf("All test cases passed successfully! :))\n");

	return 1;
}
#elif(__BALANCED_PARENTHESES__ ==1)
int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	TestCase1();

	/* if no assertion error happened, print all tests passed message. */
	printf("All test cases passed successfully! :))\n");

	return 1;
}

#else
int main(void)
{

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	/*local Variable*/
	uint8_t expression[101],value = 6,Counter_Loop=0,dummy=0;
	/* ask user to enter expression*/
	printf("Please enter an expression (maximum 100 characters long)\n");
	/* save expression entered by user in the array */
	for(Counter_Loop = 0 ; ( (dummy = getchar()) != '\n' ) ; Counter_Loop++)
	{
		expression[Counter_Loop]=dummy;
	}
	/* print the result of the balancedParentheses API to the user */
	value = balancedParentheses(expression);
	if(value==1)
	{
		printf("Balanced");
	}
	else
	{
		printf("Not Balanced");
	}
	return 1;
}

#endif
