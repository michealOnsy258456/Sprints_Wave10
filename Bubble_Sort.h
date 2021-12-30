/*
 * Sort.h
 *
 *  Created on: Dec 28, 2021
 *      Author: Micheal-Onsy
 */

#ifndef BUBBLE_SORT_H_
#define BUBBLE_SORT_H_


/*****************************************************************
*                      Includes                                 
*****************************************************************/

#include <stdio.h>
#include <assert.h>
#include "std_types.h"


/*****************************************************************
*                      Local Macros
*****************************************************************/

#define SORTED 1
#define NOT_SORTED 0

/*****************************************************************
 *                      LOCAL FUNCTIONS PROTOTYPES
*****************************************************************/
void bubblesort(uint32_t * arr,  uint8_t size);
uint8_t is_sorted(uint32_t * arr, uint8_t size);
void SortTestCases(void);


#endif /* BUBBLE_SORT_H_ */
