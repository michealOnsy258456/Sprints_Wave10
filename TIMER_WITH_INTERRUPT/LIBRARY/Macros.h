/*
 * Macros.h
 *
 *  Created on: Jan 2, 2022
 *      Author: Micheal-Onsy
 */

#ifndef MACROS_H_
#define MACROS_H_


#define Set_Bit(reg,bit)             (reg|=((uint8_t)1<<bit))

#define Clr_Bit(reg,bit)             (reg&=~((uint8_t)1<<bit))

#define Toggle_Bit(reg,bit)         (reg^=((uint8_t)1<<bit))

#define Get_Bit(reg,bit)            (((reg>>bit)&(uint8_t)(0x01)))


#endif /* MACROS_H_ */
