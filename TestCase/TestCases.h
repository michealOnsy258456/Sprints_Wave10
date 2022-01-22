/*
 * TestCases.h
 *
 *  Created on: Jan 19, 2022
 *      Author: Micheal-Onsy
 */

#ifndef TESTCASE_TESTCASES_H_
#define TESTCASE_TESTCASES_H_
#include "ADC.h"
 /*- LOCAL MACROS
 ------------------------------------------*/
#define NUMBER_OF_TESTCASES		(uint8_t)(13)
#define INVALID_CHANNEL				(uint8_t)(20)

 /*- LOCAL FUNCTIONS PROTOTYPES
 ----------------------------*/
void CallBackFunc();
void TestBeforeInit(void);
void TestInit(void);
void TestRead(void);
void TestEnableInterrupt(void);
void TestDisableInterrupt(void);


/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern const uint8_t ADC_REFERENCE_SELECTION;
extern const uint8_t ADC_CONTROL_MASK;
extern void (*g_Callback)(void);

#endif /* TESTCASE_TESTCASES_H_ */
