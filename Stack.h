/*
 * Stack.h
 *
 *  Created on: Dec 28, 2021
 *      Author: Micheal-Onsy
 */

#ifndef STACK_H_
#define STACK_H_

/*****************************************************************
*                      Includes
*****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "std_types.h"

/*****************************************************************
*                      Local Macros
*****************************************************************/
#define MAX_STACK_SIZE 100
#define EMPTY_STACK 0

struct node{
	struct node * next;
	uint8_t data;
};

/********************* global variable  ******************/
extern struct node * head;

/* string to save check to be printed and can be used in test cases. */
extern char * Check;

/* global value store current value of stack to be used in unit testing. */
extern uint8_t stack_size;



/*****************************************************************
*                      LOCAL FUNCTIONS PROTOTYPES
*****************************************************************/
/* Function to push data to stack. */
void push(uint8_t u8_data);
/* Function to pop data on top of stack */
uint8_t pop();
/* Function to print the content of the stack. */
void printStack();
/* Function to Fill the stack. */
void FillStack(void);



#endif /* STACK_H_ */
