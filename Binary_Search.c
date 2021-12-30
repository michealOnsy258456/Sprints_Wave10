/*
 * Search.c
 *
 *  Created on: Dec 28, 2021
 *      Author: Micheal-Onsy
 */


/*****************************************************************
*                      Includes
*****************************************************************/
#include "Binary_Search.h"

/************************************************************************************
* Variable (in): arr - array to be searched.
*				   size - size of array
*				   number - number to be searched
* Return : index of the found element in the array.
* Description: search a number in a given array and returns index.
************************************************************************************/
uint8_t binarySearch(uint32_t * arr, uint8_t size, uint32_t number)
{
	/* initialize found index to not found */
	uint8_t index = NOT_FOUND ;

	/* check if array is sorted or not */
	uint8_t sorted_status = is_sorted(arr, size);

	/* initialize variables used in binary search */
	uint8_t start_index = 0, end_index = size, middle = size / 2;

	/* sort array if not sorted */
	if (NOT_SORTED == sorted_status)
	{
		bubblesort(arr, size);

	}
	printf(" ****************Array After Sort**************\n");
	for(int i = 0 ; i < size ; i++ )
	{
		printf("%d\n",arr[i]);
	}

	/* binary search algorithm */
	while (start_index <= end_index)
	{
        middle = start_index + (end_index - end_index) / 2;
        if (arr[middle] == number)
		{
			index = middle;
			return index;
		}
        if (arr[middle] < number)
            start_index = middle + 1;
        else
            end_index = middle - 1;
	}

	/* return it does not found element in specific */
	return index;
}



