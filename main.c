/*
 * main.c
 *
 *  Created on: Dec 28, 2021
 *      Author: Micheal-Onsy
 */

/*****************************************************************
*                      Includes                                 
*****************************************************************/

#include <stdio.h>
#include "Binary_Search.h"
#include "Bubble_Sort.h"

/*****************************************************************
*                      Local Macros
*****************************************************************/

#define __SEARCH_TEST_CASE__ 0
#define __SORT_TEST_CASE__ 0



#if (__SEARCH_TEST_CASE__ ==  1)
#include "SearchTestCases.h"
void main(void)
{
	SearchTestCases();
	printf("All test cases passed successfully! :))\n");
}

#elif(__SORT_TEST_CASE__ ==  1)
#include "SortTestCases.h"
void main(void)
{
	SortTestCases();
	IsSortedTestCases();

	printf("All test cases passed successfully! :))\n");
}

#else
#define NOT_FOUND 255
#define MAX_INDEX 255
uint32_t user_response=0;

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	/* local variables */
	uint32_t size;
	uint32_t number;
	uint8_t index;
	uint32_t arr[MAX_INDEX];

	/* get size of array */
	printf("Please enter the size of your array. (maximum size is 255): \n");

	/* check if valid array size */
	do
	{

		scanf("%d", &size);
		if (size > MAX_INDEX)
			printf("you entered a number more than the maximum, making the entered size is 255! \n");

	}	while(size > MAX_INDEX);

	/* take array elements */
	printf("enter your array elements delimited by press Enter: \n");
	for (int i = 0; i < size; i++)
	{
		scanf("%d", &arr[i]);
	}


	/* get number to be searched */
	printf("enter the number to be searched: \n");
	scanf("%d", &number);

	/* search array for the number */
	index = binarySearch(arr, (uint8_t)size, number);


	/* print to the user the number index */
	if (index == NOT_FOUND)
	{
		printf("the entered number doesn't exist in the array. \n");
	}
	else
	{
		printf("this number is found in a sorted array in index %d \n", index);
	}

	return 1;
}
#endif


