 /******************************************************************************
 *
 * Module: I2C(TWI)
 *
 * File Name: i2c.h
 *
 * Description: Header file for the I2C(TWI) AVR driver
 *
 * Author: Micheal Onsy
 *
 *******************************************************************************/ 


#ifndef I2C_H_
#define I2C_H_

#include "../../Library/Register.h"
#include "../../Library/Std_type.h"
#include "../../LIBRARY/common_macros.h"


//PERSCALER IN TWI
#define PRESCALER_1  0b11111100
#define PRESCALER_4  0b11111101
#define PRESCALER_16 0b11111110
#define PRESCALER_64 0b11111111

/*-----------MACROS-------------*/
/*
 * It's 7-Bit address in the TWI_Adress_REGISTER for Bit 1 to bit 7
 * Bit-0 is TWI General Call Recognition Enable Bit
 * Addresses from 0b1111000 To 0b1111111 Are reserved, Can't Use!!
 * Address 0b0000000 is for General Call  Can't Use!!
*/
#define SlaveAddr (uint8_t)0x18

/*
 *According to this equ. SCL freq.=(Cpu Clock Freq)/(16+2*(Bit rate)*4^prescaler)
 *choose the prescaler and the bit rate while the clock freq. is 8000000HZ
 *the SCL should be less than 400000HZ
 */
/*THIS MACRO CONTROLS THE PRESCALER
 * PRESCALER_1
 * PRESCALER_4
 * PRESCALER_16
 * PRESCALER_64
 * */
#define Prescaler  PRESCALER_1 //choose the Prescaler 0--> 1 // 1--> 4 // 2-->16 // 3--> 64
#define Bit_rate   30//choose the value between 0 to 255 to meet the requirements
/* I2C Status Bits in the TWSR Register */
#define TW_START         0x08 /* Start has been sent */
#define TW_REP_START     0x10 /* Repeated start */
#define TW_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + Ack received from slave */
#define TW_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + Ack received from slave */
#define TW_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave */
#define TW_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave */
#define TW_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave */

/*-----------MACROS-------------*/
#define TWI_1 (uint8_t)1

/*-----------FUNCTION DECLERATIONS-------------*/

void TWI_SetSlaveAddress(void) ;
void TWI_Init();
void TWI_SendStartCondition();
void TWI_SendStopCondition( );
void TWI_SendSLAWrite(uint8_t SlvAdr);
void TWI_SendSLARead( uint8_t SlvAdr);
void TWI_SendData(uint8_t Data);
void TWI_SendChar( uint8_t SlvAdr, uint8_t Data);
void TWI_RecDataAck( uint8_t* data);
void TWI_RecChar( uint8_t SlvAdr, uint8_t* Data);
void TWI_EnableInterrupt( );
void TWI_DisableInterrupt( );
void TWI_SlaOperDetermination(  uint8_t* Oper);
void TWI_SetCallback(  Ptr_VoidFuncVoid_t Callback);
uint8_t TWI_readWithNACK(void);
uint8_t TWI_getStatus(void);



#endif /* I2C_H_ */
