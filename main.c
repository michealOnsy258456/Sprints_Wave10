/*

 * main.c
 *
 *  Created on: Jan 19, 2022
 *      Author: Micheal-Onsy
 */

#include "APP.h"
#include "TestCases.h"
int main(void)
{
	/*test cases */
	TestInit();
	TestSendCmd();
	TestSendChar();
	TestSendString();


	/* My Application */
	APP_VidInit();

	return 1;
}

