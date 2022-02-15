/*
 * external_interrupt_Lcfg.c
 *
 * Created: 2/15/2022 4:58:14 PM
 *  Author: Ahmed_Ayman
 */ 

#include "external_interrupt_Lcfg.h"

PUBLIC EXIT_Handler_t  EXIT_Handler = {.EXTI_EDGE_DETECTION = EXTI_EDGE_RISING_EDGE ,.EXTI_NUM =EXTI_NUM_2};