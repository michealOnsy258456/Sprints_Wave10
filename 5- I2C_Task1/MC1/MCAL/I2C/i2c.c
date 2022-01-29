/******************************************************************************
 *
 * Module: I2C(TWI)
 *
 * File Name: i2c.c
 *
 * Description: Source file for the I2C(TWI) AVR driver
 *
 * Author: Micheal Onsy
 *
 *******************************************************************************/
/*******************************************************************************
 *                            Includes                                         *
 *******************************************************************************/
#include "i2c.h"

/*******************************************************************************
 *                            GLOBAL STATIC VARIABLES                          *
 *******************************************************************************/
Ptr_VoidFuncVoid_t G_TWI_CALLBACK=NULL_PTR;


/*******************************************************************************
 *                            LOCAL MACROS                                     *
 *******************************************************************************/

// TWI_Control_REGISTER
#define TWINT      7
#define TWEA       6
#define TWSTA      5
#define TWSTO      4
#define TWWE       3
#define TWEN       2
#define RESERVED   1
#define TWIE       0

#define EN_TWI     0b00000100
#define SEND_STOP  0b00010000
#define SEND_START 0b00100000
#define SEND_ACK   0b01000000
#define CLR_FLAG   0b10000000

/*******************************************************************************
 *                            APIs IMPLEMENTATION                               *
 *******************************************************************************/

/*******************************************************************************
 * brief: Function To Set Slave address                                        *
 *******************************************************************************/
void TWI_SetSlaveAddress(void)
{
	TWAR = (SlaveAddr << 1); //Shift the register left
}
/*******************************************************************************
 * brief: Function To Initialize TWI Module                                    *
 *******************************************************************************/
void TWI_Init()
{
	/*-----SET ADDRESS IN CASE OF IT'S IN SLAVE MODE---- */
	TWI_SetSlaveAddress();
	/*-----SETTING THE FREQ-----*/
	TWBR = Bit_rate;
	TWSR &= Prescaler;
	/*Initial Value for TWI_Control_REGISTER is zeros so I set only what I need and ignore the rest*/
	/*-----ENABLE ACKNOWLEDGE----*/
	Set_Bit(TWCR, TWEA);
	/*-----ENABLE THE PREIPHERAL ITSELF-----*/
	Set_Bit(TWCR, TWEN);
}

/*******************************************************************************
 * brief: Function To Start TWI Module                                          *
 *******************************************************************************/
void TWI_SendStartCondition( )
{
	TWCR = (1<<TWEN)|(1<<TWSTA)|(1<<TWINT);//(EN_TWI | SEND_START | CLR_FLAG);
	while ((Get_Bit(TWCR, TWINT)) != 1)
		;/*Wait for TWINT Flag set.
		 This indicates that the START condition has been transmitted*/
}
/*******************************************************************************
 * brief: Function To Stop TWI Module                                          *
 *******************************************************************************/
void TWI_SendStopCondition( )
{
	/*Wait for TWINT Flag set.
			 This indicates that the STOP condition has been transmitted*/
	TWCR =(1<<TWEN)|(1<<TWSTO)|(1<<TWINT); //(EN_TWI | CLR_FLAG | SEND_STOP);
}
/*******************************************************************************
 * brief: Function To Write Address about another module                    *
 *******************************************************************************/
void TWI_SendSLAWrite(uint8_t SlvAdr)
{

	TWDR = ((SlvAdr << 1) | 0);
	TWCR = (1<<TWEN)|(1<<TWINT);//(EN_TWI | CLR_FLAG);// CLEAR FLAG TO SEND DATA
	while (Get_Bit(TWCR,TWINT) == 0)
		;

}
/*******************************************************************************
 * brief: Function To Read From another module                              *
 *******************************************************************************/
void TWI_SendSLARead(  uint8_t SlvAdr) {
	TWDR = ((SlvAdr << 1) | 1);
	TWCR = (EN_TWI | CLR_FLAG);
	while (Get_Bit(TWCR,TWINT) == 0)
		;
}
/*******************************************************************************
 * brief: Function To Write data in another module                          *
 *******************************************************************************/
void TWI_SendData(  uint8_t Data){
	TWDR = Data;
	TWCR = (1<<TWEN)|(1<<TWINT);//(EN_TWI | CLR_FLAG);
	while (Get_Bit(TWCR,TWINT) == 0)
		;
}

/*******************************************************************************
 * brief: Function To Get the Status About TWI                                *
 *******************************************************************************/
uint8_t TWI_getStatus(void)
{
    uint8_t status;
    /* Masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    status = TWSR & 0xF8;
    return status;
}
/*******************************************************************************
 * brief: Function To Send character to another module                         *
 *******************************************************************************/
void TWI_SendChar(  uint8_t SlvAdr, uint8_t Data)
{
	uint8_t au8_counter =0;
	/*SENDING START CONDITION*/
	for(au8_counter=0;au8_counter<100;au8_counter++);
	TWI_SendStartCondition();
	/*--SEND SALVE ADDRESS WITH WRITE OPERATION--*/
	TWI_SendSLAWrite(SlvAdr);
	for(au8_counter=0;au8_counter<100;au8_counter++);
	/*--SENDING DATA--*/
	TWI_SendData(Data);
	for(au8_counter=0;au8_counter<100;au8_counter++);
	/*--SENDING STOP CONDITION*/
	TWI_SendStopCondition();

}
/*******************************************************************************
 * brief: Function To Read with acknowladge from another module                *
 *******************************************************************************/
void TWI_RecDataAck( uint8_t* data)
{
	TWCR|=(TWEA<<1);
	while (Get_Bit(TWCR,TWINT) == 0)
		;
	*data = TWDR;
}
/*******************************************************************************
 * brief: Function To Read without acknowladge from another module                *
 *******************************************************************************/

uint8_t TWI_readWithNACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT = 1
	 * Enable TWI Module TWEN = 1
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);

    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));

    /* Read Data */
    return TWDR;
}
/*******************************************************************************
 * brief: Function To Read character from another module                       *
 *******************************************************************************/
void TWI_RecChar( uint8_t SlvAdr, uint8_t* Data)
{
	/*SENDING START CONDITION*/

	TWI_SendStartCondition();
	/*--SEND SALVE ADDRESS WITH Read OPERATION--*/
	TWI_SendSLARead( SlvAdr);
	/*--READ DATA FROM ANOTHER DEVICE WITH ACKNOWLADGE*/
	TWI_RecDataAck( Data);
	/*--SENDING STOP CONDITION*/
	TWI_SendStopCondition();
}
/*******************************************************************************
 * brief: Function To Enable Interrupt for this module                           *
 *******************************************************************************/
void TWI_EnableInterrupt( )
{
	Set_Bit(TWCR, TWIE); //Disable ISR for the TWI peripheral
}
/*******************************************************************************
 * brief: Function To Disable Interrupt for this module                           *
 *******************************************************************************/
void TWI_DisableInterrupt( )
{
	CLEAR_BIT(TWCR, TWIE); //Disable ISR for the TWI peripheral
}
void TWI_SlaOperDetermination(  uint8_t* Oper)
{
	*Oper = Get_Bit(TWDR, 0);
}
/*******************************************************************************
 * brief: Function To Set Interrupt for this module                           *
 *******************************************************************************/
void TWI_SetCallback( Ptr_VoidFuncVoid_t Callback)
{
	G_TWI_CALLBACK = Callback;
}
/*******************************************************************************
 * brief: Function To write Interrupt with here                                 *
 *******************************************************************************/
void __vector_19(void) __attribute__((signal)); // Serial Transfer Complete
void __vector_19(void)
{
	G_TWI_CALLBACK();
}
