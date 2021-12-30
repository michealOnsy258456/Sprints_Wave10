/*
 * SortTestCases.c
 *
 *  Created on: Dec 29, 2021
 *      Author: Micheal-Onsy
 */
/*****************************************************************
*                      Includes                                 
*****************************************************************/

#include "SortTestCases.h"

/*****************************************************************
 *                       FUNCTIONS 
*****************************************************************/
void SortTestCases(void)
{

	uint32_t size_one_array[1] = { 100 };
    printf("Pass test case : it sorted array that has one member in array \n");
	bubblesort(size_one_array, 1);
	assert(size_one_array[0] == 100);

	uint32_t reverse_arr[] = { 9,8,7,6,5,4,3,2,1,0 };
    printf("Pass test case : it sorted reverse array that has a lot of data with specific size \n");
	bubblesort(reverse_arr, 10);
	for (int i = 0; i < 10; i++)
	{
		assert(reverse_arr[i] == i);
	}

	uint32_t random_arr[] = { 1,2,5,6,4,3,7,9,8,0 };
    printf("Pass test case : it sorted random array that has member in array \n");
	bubblesort(random_arr, 10);
	for (int i = 0; i < 10; i++)
	{
		assert(random_arr[i] == i);
	}
}

void IsSortedTestCases(void)
{
	uint8_t sort_status;

	uint32_t not_sorted_arr[] = { 1,2,5,6,4,3,7,9,8,0 };
	sort_status = is_sorted(not_sorted_arr, 10);
    printf("Pass test case : it sorted not sort array that has member in array \n");
	assert(sort_status == NOT_SORTED);

	uint32_t sorted_arr[] = { 0,1,2,3,4,5 };
	sort_status = is_sorted(sorted_arr, 6);
    printf("Pass test case : it sorted array that is sorted \n");
	assert(sort_status == SORTED);
}

