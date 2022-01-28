/*
 * Macros.h
 *
 *  Created on: Jan 19, 2022
 *      Author: Micheal-Onsy
 */

#ifndef LIBRARY_COMMON_MACROS_H_
#define LIBRARY_COMMON_MACROS_H_

#define Get_Bit(REG,bit)                        (((REG>>bit)&(0x01)))


/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))

/* Rotate right the register value with specific number of rotates */
#define ROR(REG,num) ( REG= (REG>>num) | (REG<<(8-num)) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,num) ( REG= (REG<<num) | (REG>>(8-num)) )

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )




/* Set_Bit --> Sets any bit ( ON )*/
/* To set a bit, We use (Inclusive OR) as ( 0 --> Makes No change ) and ( 1 --> Sets ON )   */
#define Set_Bit(reg,bit)             (reg|=((uint8_t)1<<bit))
#define Set_Low_Nibble(reg)          (reg|=((uint8_t)0x0f))
#define Set_High_Nibble(reg)         (reg|=((uint8_t)0xf0))
#define Set_Byte(reg)                (reg=((uint8_t)0xff))

/* Clr_Bit --> Sets any bit ( OFF ) == ( Clear any bit )*/
/* To clear a bit, We use ( And ) as ( 1 --> Makes No change ) and ( 0 --> Sets OFF )   */
#define Clr_Bit(reg,bit)             (reg&=~((uint8_t)1<<bit))
#define Clr_Low_Nibble(reg)          (reg&=((uint8_t)0xf0))
#define Clr_High_Nibble(reg)         (reg&=((uint8_t)0x0f))
#define Clr_Byte(reg)                (reg=((uint8_t)0x00))


/* Toggle_Bit --> Flip any bit  */
/* To Flip a bit, We use ( Exclusive OR ) as ( 0 --> Makes No change ) and ( 1 --> Toggle )   */
#define Toggle_Bit(reg,bit)         (reg^=((uint8_t)1<<bit))
#define Toggle_Low_Nibble(reg)      (reg^=((uint8_t)0x0f))
#define Toggle_High_Nibble(reg)     (reg^=((uint8_t)0xf0))
#define Toggle_Byte(reg)            (reg^=((uint8_t)0xff))


#endif /* LIBRARY_COMMON_MACROS_H_ */
