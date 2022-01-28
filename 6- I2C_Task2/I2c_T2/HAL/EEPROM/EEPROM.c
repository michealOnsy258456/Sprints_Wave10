 /******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: external_eeprom.c
 *
 * Description: Source file for the External EEPROM Memory
 *
 * Author: Micheal Onsy
 *
 *******************************************************************************/
/*******************************************************************************
 *                            Includes                                         *
 *******************************************************************************/
#include "../../MCAL/I2C/i2c.h"
#include "EEPROM.h"
/*******************************************************************************
 * brief: Function To Initialize EEPROM                                         *
 *******************************************************************************/
void EEPROM_init(void)
{
	/* just initialize the I2C(TWI) module inside the MC */
	TWI_Init();
}
/*******************************************************************************
 * brief: Function To Write in EEPROM                                         *
 *******************************************************************************/
uint8_t EEPROM_writeByte(uint16_t u16addr, uint8_t u8data)
{
	/* Send the Start Bit */
	TWI_SendStartCondition();
    if (TWI_getStatus() != TW_START)
        return ERROR;
		
    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    TWI_SendData((uint8_t)(0xA0 | ((u16addr & 0x0700)>>7)));
    if (TWI_getStatus() != TW_MT_SLA_W_ACK)
        return ERROR; 
		 
    /* Send the required memory location address */
    TWI_SendData((uint8_t)(u16addr));
    if (TWI_getStatus() != TW_MT_DATA_ACK)
        return ERROR;
		
    /* write byte to eeprom */
    TWI_SendData(u8data);
    if (TWI_getStatus() != TW_MT_DATA_ACK)
        return ERROR;

    /* Send the Stop Bit */
    TWI_SendStopCondition();
	
    return SUCCESS;
}
/*******************************************************************************
 * brief: Function To Read   in EEPROM                                         *
 *******************************************************************************/
uint8_t EEPROM_readByte(uint16_t u16addr, uint8_t *u8data)
{
	/* Send the Start Bit */
	TWI_SendStartCondition();
    if (TWI_getStatus() != TW_START)
        return ERROR;
		
    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    TWI_SendData((uint8_t)((0xA0) | ((u16addr & 0x0700)>>7)));
    if (TWI_getStatus() != TW_MT_SLA_W_ACK)
        return ERROR;
		
    /* Send the required memory location address */
    TWI_SendData((uint8_t)(u16addr));
    if (TWI_getStatus() != TW_MT_DATA_ACK)
        return ERROR;
		
    /* Send the Repeated Start Bit */
    TWI_SendStartCondition();
    if (TWI_getStatus() != TW_REP_START)
        return ERROR;
		
    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=1 (Read) */
    TWI_SendData((uint8_t)((0xA0) | ((u16addr & 0x0700)>>7) | 1));
    if (TWI_getStatus() != TW_MT_SLA_R_ACK)
        return ERROR;

    /* Read Byte from Memory without send ACK */
    *u8data = TWI_readWithNACK();
    if (TWI_getStatus() != TW_MR_DATA_NACK)
        return ERROR;

    /* Send the Stop Bit */
    TWI_SendStopCondition();
    return SUCCESS;
}
