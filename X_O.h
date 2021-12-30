/*
 * X_O.h
 *
 *  Created on: Dec 27, 2021
 *      Author: Micheal-Onsy
 */

#ifndef X_O_H_
#define X_O_H_

/*****************************************************************
*                      Includes                                 
*****************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "std_types.h"


/*****************************************************************
*                      ENUM                                     
*****************************************************************/
typedef unsigned char bool_t;
 typedef enum
 {
	E_ENTERED_NUMBER_OUTSIDE_LIMITS,
	E_ENTERED_NUMBER_WITHIN_LIMITS,
    E_ENTERED_NUMBER_USED_BEFORE,
    E_ENTERED_NUMBER_NOT_USED_BEFORE
 }E_status;


/*****************************************************************
*                      Local Macros
*****************************************************************/
#define Winner 1
#define EndOfGameWithoutNoOneWin 2
#define StillThePlacesEmpty 3
#define E_OK 0
#define E_INVALID_POSITION 1
#define E_ALREADY_TAKEN_POSITION 2



/*****************************************************************
*                      LOCAL FUNCTIONS PROTOTYPES
*****************************************************************/
/*Function to identify the player*/
void Identify_The_Name_Player();
/*Function to draw the shape to the user*/
void drawGame();
/*Function to save the mark player */
E_status Save_Player_Mark(uint8_t pos);
/*Function to check who is win or the places has empty mark or end without no one win*/
uint8_t checkwin();
/*Function to check who is win*/
void Check_The_Choice_Who_is_Win(uint8_t Choice);
E_status XO_ECheckTheUsage(uint8_t LOC_u8Pos);
E_status XO_ECheckThePos(uint8_t Data);
#endif /* X_O_H_ */
