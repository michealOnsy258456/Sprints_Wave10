/*
 * Search.h
 *
 *  Created on: Dec 28, 2021
 *      Author: Micheal-Onsy
 */

#ifndef BINARY_SEARCH_H_
#define BINARY_SEARCH_H_

/*****************************************************************
*                      Includes
*****************************************************************/
#include <stdio.h>
#include "Bubble_Sort.h"
#include "std_types.h"
#include <assert.h>


/*****************************************************************
*                      Local Macros
*****************************************************************/
#define NOT_FOUND 255
#define SORTED 1
#define NOT_SORTED 0

/*****************************************************************
 *                      LOCAL FUNCTIONS PROTOTYPES
*****************************************************************/

/* Function to search an arry for an element. */
uint8_t binarySearch(uint32_t * arr, uint8_t size, uint32_t number);
void SearchTestCases();

#endif /* BINARY_SEARCH_H_ */
