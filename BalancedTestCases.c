/*
 * BalancedTestCases.c
 *
 *  Created on: Dec 29, 2021
 *      Author: Micheal-Onsy
 */

#include "BalancedTestCases.h"



/************************************************************************************
* Description: checks multiple expressions if they are balanced or not.
************************************************************************************/
void TestCase1(void)
{
	/* Balanced Cases */
	assert(balancedParentheses("(2*3+(5/2+(4*3)))") == BALANCED_MESSAGE);
	assert(balancedParentheses("3") == BALANCED_MESSAGE);
	assert(balancedParentheses("({2+3}*(4+5))") == BALANCED_MESSAGE);
	assert(balancedParentheses("{}")== BALANCED_MESSAGE);
	assert(balancedParentheses("()")== BALANCED_MESSAGE);
	assert(balancedParentheses("({})") == BALANCED_MESSAGE);
	assert(balancedParentheses("((){})")== BALANCED_MESSAGE);

	/* Not Balanced Cases */
	assert(balancedParentheses("{({2+10}}*11}") == NOT_BALANCED_MESSAGE);
	assert(balancedParentheses("({3)}")== NOT_BALANCED_MESSAGE);
	assert(balancedParentheses("(}")== NOT_BALANCED_MESSAGE);
	assert(balancedParentheses("({}")== NOT_BALANCED_MESSAGE);
	assert(balancedParentheses("}{)(")== NOT_BALANCED_MESSAGE);

}
