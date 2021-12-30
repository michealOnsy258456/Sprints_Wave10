/*
 * SearchTestCases.c
 *
 *  Created on: Dec 29, 2021
 *      Author: Micheal-Onsy
 */


/*****************************************************************
*                      Includes                                 
*****************************************************************/

#include "SearchTestCases.h"

/*****************************************************************
 *                       FUNCTIONS
*****************************************************************/
void SearchTestCases(void)
{
	uint32_t arr[] = { 0,1,2,3,4,5,6,7,8,9 };
    printf("Pass test case : it search in array to specific data\n");
	assert(binarySearch(arr, SIZE_OF_ARRAY, 5) == 5);
    printf("Pass test case : it search in array to dummy data \n");
	assert(binarySearch(arr, SIZE_OF_ARRAY, 30) == (uint8_t)NOT_FOUND);

	uint32_t unsorted_arr[] = { 9,8,5,1,3,2,6,0,4,7 };
    printf("Pass test case : it search in unsorted array to specific data \n");
	assert(binarySearch(unsorted_arr, SIZE_OF_ARRAY, 3) == 3);
	assert(binarySearch(unsorted_arr, SIZE_OF_ARRAY, 90) == (uint8_t)NOT_FOUND);

}
