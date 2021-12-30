/*
 * Sort.c
 *
 *  Created on: Dec 28, 2021
 *      Author: Micheal-Onsy
 */

/*****************************************************************
*                      Includes                                 
*****************************************************************/
#include "Bubble_Sort.h"

/************************************************************************************
* Variable (in): arr - array to be sorted.
*				   size - size of array
* Return : None
* Description: sorts an array using Bubble sort.
************************************************************************************/
void bubblesort(uint32_t * arr,  uint8_t size)
{
	/*Local variable*/
	unsigned char temp ,j,i;

	/* Bubble sort algorithm */
	for (i = 0; i < size-1; i++)
	{
		for (j = 0 ; j < (size-i-1) ; j++)
		{
			if (arr[j] > arr[j+1])
			{
				temp= arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
}


/************************************************************************************
* Variable (in): arr - array to be checked if it is a sorted array.
*				   size - size of arrays
* Return : returns SORTED or NOT_SORTED.
* Description: check if a given array is sorted.
************************************************************************************/

uint8_t is_sorted(uint32_t * arr, uint8_t size)
{
	/*Local Variable*/
	uint8_t sorted_status = SORTED , i ;


	/* check if array is not sorted */
	for (i = 1; i < size; i++)
	{
		if (arr[i] < arr[i - 1])
		{
			sorted_status = NOT_SORTED;
			break;
		}
	}

	return sorted_status;
}


