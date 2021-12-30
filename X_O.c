/*
 * X_O.c
 *
 *  Created on: Dec 27, 2021
 *      Author: Micheal-Onsy
 */




/*****************************************************************
 *                      Includes
*****************************************************************/
#include "X_O.h"

/* global variable used to store X and O entered by players. */
uint8_t gau8_mark[10] = {'0','1', '2', '3', '4', '5', '6', '7', '8', '9' };

/* global variable used to determine which player turn */
uint8_t *player1 , *player2;
uint8_t gau8_player_turn=1, position,Mark;

/************************************************************************************
* Description: Function prints the current player_marks array in a visual way for
*			   the players while asking the next player to enter the position for
*			   the gau8_mark.
************************************************************************************/
void drawGame()
{
	system("cls");
	printf("Welcome %s and %s in  X O game \n\n\n",&player1,&player2);

	printf("%s (X) %s (O)\n\n\n",&player1,&player2);

	/* print the board with the available positions and the taken positions */
	printf(" ____ ____ ____\n");
	printf("|    |    |    |\n");
	printf("|  %c |  %c | %c  |\n", gau8_mark[1], gau8_mark[2], gau8_mark[3]);
	printf("|____|____|____|\n");
	printf("|    |    |    |\n");
	printf("|  %c |  %c | %c  |\n", gau8_mark[4], gau8_mark[5], gau8_mark[6]);
	printf("|____|____|____|\n");
	printf("|    |    |    |\n");
	printf("|  %c |  %c | %c  |\n", gau8_mark[7], gau8_mark[8], gau8_mark[9]);
	printf("|____|____|____|\n\n\n");

	/* print to the user to give the position he wants */


	printf
	(
			"Player %d please enter the position to put the %c mark : ",
			gau8_player_turn % 2 == 1 ? 1 : 2,
					gau8_player_turn % 2 == 1 ? (Mark='X') : (Mark='O')
	);
}
/************************************************************************************
* Description: Function to identify the name of the player
************************************************************************************/

void Identify_The_Name_Player()
{
	printf("Enter the name of first player  : ");
	scanf("%s",&player1 );

	printf("Enter the name of second player : ");
	scanf("%s",&player2);
}

/************************************************************************************
* Parameters (in): the position to put the gau8_mark in
* Return value: LOC_EStatus
* Description: Function to save the Mark put by player in marks array
************************************************************************************/

E_status Save_Player_Mark(uint8_t pos)
{
	/* variable to store the error status */
	E_status LOC_EStatus = E_ENTERED_NUMBER_OUTSIDE_LIMITS;
	LOC_EStatus = XO_ECheckThePos(pos);
	if (LOC_EStatus == E_ENTERED_NUMBER_OUTSIDE_LIMITS)
	{
		/*Do Nothing*/
	}
	else if (LOC_EStatus == E_ENTERED_NUMBER_WITHIN_LIMITS)
	{
		LOC_EStatus = XO_ECheckTheUsage(pos);
		if (LOC_EStatus == E_ENTERED_NUMBER_NOT_USED_BEFORE)
		{
			/* check if the position given is not already taken */
			if (pos == 1)
			{
				gau8_mark[1] = Mark;
			}
			else if (pos == 2)
			{
				gau8_mark[2] = Mark;
			}
			else if (pos == 3)
			{
				gau8_mark[3] = Mark;
			}
			else if (pos == 4)
			{
				gau8_mark[4] = Mark;
			}
			else if (pos == 5)
			{
				gau8_mark[5] = Mark;
			}
			else if (pos == 6)
			{
				gau8_mark[6] = Mark;
			}
			else if (pos == 7)
			{
				gau8_mark[7] = Mark;
			}
			else if (pos == 8)
			{
				gau8_mark[8] = Mark;
			}
			else if (pos == 9)
			{
				gau8_mark[9] = Mark;
			}
			else
			{
				/* Do Nothing*/
			}
		}
		else if (LOC_EStatus == E_ENTERED_NUMBER_USED_BEFORE)
		{
			/*Do Nothing*/
		}		
	}
	gau8_player_turn++;
	return LOC_EStatus;
}

/************************************************************************************
* Return value: data to till who is Winner , EndOfGameWithoutNoOneWin and StillThePlacesEmpty
* Description: Function to show who is Winner , EndOfGameWithoutNoOneWin and StillThePlacesEmpty.
************************************************************************************/
uint8_t checkwin()
{
	/* check if there is a horizontal line formed. */
	if ((gau8_mark[1] == gau8_mark[2]) && (gau8_mark[2] == gau8_mark[3]))
		return Winner;
	else if ((gau8_mark[4] == gau8_mark[5]) && (gau8_mark[5] == gau8_mark[6]))
		return Winner;
	else if ((gau8_mark[7] == gau8_mark[8]) && (gau8_mark[8] == gau8_mark[9]))
		return Winner;

	/* check if there is a vertical line formed. */
	else if ((gau8_mark[1] == gau8_mark[4]) && (gau8_mark[4] == gau8_mark[7]))
		return Winner;
	else if ((gau8_mark[2] == gau8_mark[5]) && (gau8_mark[5] == gau8_mark[8]))
		return Winner;
	else if ((gau8_mark[3] == gau8_mark[6]) && (gau8_mark[6] == gau8_mark[9]))
		return Winner;

	/* check if there is a diagonal line formed. */
	else if ((gau8_mark[1] == gau8_mark[5]) && (gau8_mark[5] == gau8_mark[9]))
		return Winner;
	else if ((gau8_mark[3] == gau8_mark[5]) && (gau8_mark[5] == gau8_mark[7]))
		return Winner;
	/* check if all place are formed  */
	else if ((gau8_mark[1] != '1') && (gau8_mark[2] != '2') && (gau8_mark[3] != '3') &&
			(gau8_mark[4] != '4') && (gau8_mark[5] != '5') && (gau8_mark[6] != '6') && (gau8_mark[7]
								 != '7') && (gau8_mark[8] != '8') && (gau8_mark[9] != '9'))
		return EndOfGameWithoutNoOneWin;

	else
		/* check and you have still the places are  empty */
		return  StillThePlacesEmpty;
}

/************************************************************************************
* Variable (in): choice to no who is win
* Description: Function to show who is win
************************************************************************************/

void Check_The_Choice_Who_is_Win(uint8_t Choice)
{
	/* clear the previous screen. */
	system("cls");
	Mark=0;
	if (Choice == Winner)
	{
		printf("\t\t **!!Player %d Wins!!**\n", gau8_player_turn % 2 == 0 ? (Mark=1) : (Mark=2));
		if (Mark==1)
		{
			printf("\t\t **!! %s Wins!!**\n", &player1);

		}
		else if (Mark==2)
		{
			printf("\t\t **!! %s Wins!!**\n", &player2);

		}
		printf("Close the console and open the game again for a new game\n");

	}
	else if(Choice == EndOfGameWithoutNoOneWin)
	{
		printf("\t\t Draw!\n");
		printf("Close the console and open the game again for a new game\n");

	}


}

/************************************************************************************
 * 									unit test						                *
 * *********************************************************************************/


/************************************************************************************
* Parameters (in): the data to check 
* Return value: LOC_EStatus
* Description: Function to check of position
************************************************************************************/

E_status XO_ECheckThePos(uint8_t Data)
{

	E_status LOC_EStatus = E_ENTERED_NUMBER_OUTSIDE_LIMITS;
	if ( (Data <= 9) )
	{ 		
		return E_ENTERED_NUMBER_WITHIN_LIMITS;
	}
	else
	{
		gau8_player_turn--;
		return E_ENTERED_NUMBER_OUTSIDE_LIMITS;
	}
}

/************************************************************************************
* Parameters (in): the data to check 
* Return value: LOC_EStatus
* Description: Function to check the place is usage before or not
************************************************************************************/
E_status XO_ECheckTheUsage(uint8_t LOC_u8Pos)
{
	uint8_t LOC_u8Counter = 0;
	E_status LOC_EStatus = E_ENTERED_NUMBER_USED_BEFORE;
	for (LOC_u8Counter = 1 ; LOC_u8Counter <=9 ; LOC_u8Counter++)
	{
		if (LOC_u8Pos == LOC_u8Counter)
		{
			if(gau8_mark[LOC_u8Counter] == (LOC_u8Counter+'0'))
			{
				LOC_EStatus = E_ENTERED_NUMBER_NOT_USED_BEFORE;
				return LOC_EStatus;
			}
			else if(gau8_mark[LOC_u8Counter] != LOC_u8Counter+'0')
			{
				gau8_player_turn--;
				LOC_EStatus = E_ENTERED_NUMBER_USED_BEFORE;
				return LOC_EStatus;
			}
		}
	}
}
