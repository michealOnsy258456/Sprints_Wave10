/*
 * main.c
 *
 *  Created on: Dec 27, 2021
 *      Author: Micheal-Onsy
 */

/*****************************************************************
*                      Includes
*****************************************************************/
#include "X_O.h"


int main ()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	/*local variable */
	uint8_t au8_check,au8_position;
	/*Function to identify the players*/
	Identify_The_Name_Player();
	/*Function to draw the game */

	drawGame();


	while(1)
	{
		/* get the player choice if valid. */
		scanf("%d",&au8_position);
		/* save the player choice. */
		au8_check = Save_Player_Mark(au8_position);

		/*au8_check On Test cases*/
		if (au8_check==E_ENTERED_NUMBER_OUTSIDE_LIMITS)
		{
			printf("Invalid position please choose another!!!\n");
			printf("Press the Enter button to resume the game.\n");
			getch();
		}
		else if(au8_check==E_ENTERED_NUMBER_USED_BEFORE)
		{
			printf("Position already taken please choose another position\n");
			printf("Press the Enter button to resume the game.\n");
			getch();

		}
		else if (au8_check==E_ENTERED_NUMBER_NOT_USED_BEFORE)
		{
			/* au8_check if now there is a straight line formed */
			au8_check= checkwin();
			if (au8_check == Winner)
			{
				break;
			}
			else if(au8_check == EndOfGameWithoutNoOneWin)
			{
				break;
			}

		}
		/* draw the board. */
		drawGame();


	}
	Check_The_Choice_Who_is_Win(au8_check);
	return 1;

}
