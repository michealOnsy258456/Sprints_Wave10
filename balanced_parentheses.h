/*
 * balanced_parentheses.h
 *
 *  Created on: Dec 28, 2021
 *      Author: Micheal-Onsy
 */

#ifndef BALANCED_PARENTHESES_H_
#define BALANCED_PARENTHESES_H_

/*****************************************************************
*                      Includes
*****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"

/*****************************************************************
*                      Local Macros
*****************************************************************/
#define BALANCED_MESSAGE 1
#define NOT_BALANCED_MESSAGE 0
#define BALANCED_STATE 1
#define NOT_BALANCED_STATE 0


/*****************************************************************
*                      LOCAL FUNCTIONS PROTOTYPES
*****************************************************************/

uint8_t checkBalance(struct node * stack_pointer);

uint8_t  balancedParentheses(uint8_t * expression);

#endif /* BALANCED_PARENTHESES_H_ */
