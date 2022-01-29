 /******************************************************************************
 *
 * [MODULE]: APPLICATION
 *
 * [FILE NAME]: App.c
 *
 * [DESCRIPTION]: Source file for the Application
 *
 * [AUTHOR]: Micheal Onsy
 *
 *******************************************************************************/
/*******************************************************************************
 *                              INCLUDES                                       *
 *******************************************************************************/
#include "App.h"

/*******************************************************************************
 *                      LOCAL FUNCTION DEFINITION                              *
 *******************************************************************************/
uint8_t ConvertCh_Dec(uint8_t * STRING_1, uint8_t *Address) ;

/*******************************************************************************
 *                              LOCAL MACRO                                     *
 *******************************************************************************/
#define ADDRESS_SIZE 7


/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
uint8_t gStr8_message[10];
uint8_t gStr8_address[10];
uint8_t gu8_WriteData;
uint8_t gu8_ReadData;
/*******************************************************************************
 * [Function Name]: App_init
 *
 * [Description]: 	Function to Initialize the application
 *
 *******************************************************************************/

void APP_Init(void)
{
	UART_Config config={UART_1StopBit,UART_8Bit,UART_AsyncDouble,UART_Disable};//configuration of uart
	UART_VidInit(&config,9600); // initialize UART driver

	EEPROM_init();	/* Initialize the external EEPROM */
}

/*******************************************************************************
 * [Function Name]: App_Update
 *
 * [Description]: 	Function to update the state of the application
 *
 *******************************************************************************/
void APP_Update(void)
{
    uint8_t au8_WriteAddr = 0;

	UART_receiveString(gStr8_message);		/* Receive string from terminal */

	/* Check if the message is write or read */
	if(strcmp(gStr8_message, "WRITE") == IDENTICAL)
	{
		UART_receiveString(gStr8_address);	/* Receive address from terminal */
		ConvertCh_Dec(gStr8_address, &au8_WriteAddr);

		UART_sendString("OK\r");				/* Receive acknowledge from terminal */
		gu8_WriteData = UART_recieveByte();		/* Receive data from terminal */

		EEPROM_writeByte(au8_WriteAddr, gu8_WriteData);	/* Write data in the external EEPROM */
		UART_sendString("\rOK\r\r");
	}
	else if(strcmp(gStr8_message, "READ") == IDENTICAL)
	{
		UART_receiveString(gStr8_address);	/* Receive string from terminal */
		ConvertCh_Dec(gStr8_address, &au8_WriteAddr);

		UART_sendString("OK\r");				/* Receive acknowledge from terminal */
		EEPROM_readByte(au8_WriteAddr, &gu8_ReadData);	/* Read data in the external EEPROM */

		UART_sendString("The data stored is ");
		UART_sendByte(gu8_ReadData);
		UART_sendString("\r\r");
	}
}



/*CONVERTS THE ADDRESS FROM CHARACTERS TO DECIMAL NUMBER*/



unsigned char ConvertCh_Dec(unsigned char * STRING_1, unsigned char *Address)
{
	unsigned char lu8_counter = 0;
	unsigned char lu8_counter2 = 0;
	*Address=0;
	while (STRING_1[lu8_counter] != '\0')
	{
		if ((STRING_1[lu8_counter] != '0') && (STRING_1[lu8_counter] != '1'))
		{
			return 2;
		}
		else
		{
			STRING_1[lu8_counter] = gStr8_address[lu8_counter] - '0';
			lu8_counter++;
		}
	}
	lu8_counter=lu8_counter-1;
	if (lu8_counter != 7)
	{
		return 1;
	}
	else
	{

	}
	while (lu8_counter2 != 8)
	{
		*Address |= (STRING_1[lu8_counter] << lu8_counter2);
		STRING_1[lu8_counter] = '\0';
		lu8_counter--;
		lu8_counter2++;
	}
	return 0;

}
