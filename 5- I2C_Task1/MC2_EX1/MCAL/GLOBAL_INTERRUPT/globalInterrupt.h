/*
 * globalInterrupt.h
 *
 *  Created on: Jan 26, 2022
 *      Author: Micheal-Onsy
 */

#ifndef MCAL_GLOBAL_INTERRUPT_GLOBALINTERRUPT_H_
#define MCAL_GLOBAL_INTERRUPT_GLOBALINTERRUPT_H_

#include"common_macros.h"
#include"Std_type.h"

void GI_EnableGI(void);
void GI_DisableGI(void);



#define SREG_REGISTER      (*((volatile uint8_t*)0x5F))

#define I_BIT 7



#endif /* MCAL_GLOBAL_INTERRUPT_GLOBALINTERRUPT_H_ */
