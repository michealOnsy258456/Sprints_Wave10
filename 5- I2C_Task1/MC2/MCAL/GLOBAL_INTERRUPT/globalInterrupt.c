/*
 * globalInterrupt.c
 *
 *  Created on: Jan 26, 2022
 *      Author: Micheal-Onsy
 */




#include"globalInterrupt.h"

void GI_EnableGI (void)
{
	SET_BIT(SREG_REGISTER,I_BIT);
}


void GI_DisableGI (void)
{
	CLEAR_BIT(SREG_REGISTER, I_BIT);
}
