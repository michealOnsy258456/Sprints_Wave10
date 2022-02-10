/*
 * LCD.c
 *
 *  Created on: Dec 29, 2019
 *      Author: micheal_onsy
 */
#include "../LCD/LCD.h"


/*TIMER1 Configuration */
TIM_Config timer_config = { TIMER_0, COMPARE, TIMER1_F_CLK_8};
/*declaring a variable for the timer return*/
static uint8_t * TimerRetVal1 =NULL_PTR;

/*Local Macros*/
#define Sending_First_Nibble								(1)
#define First_Nibble_Sent									(2)
#define Sending_Second_Nibble								(3)
#define Second_Nibble_Sent									(4)
#define LCD_Pin_Initializing								(5)
#define LCD_Start_Initialization							(6)
#define LCD_Sent_Initialization_Sequence					(7)
#define First_Cmd_Sent										(8)
#define Second_Cmd_Sent										(9)
#define Third_Cmd_Sent										(10)
#define Fourth_Cmd_Sent										(11)
#define Fifth_Cmd_Sent										(12)
#define Sixth_Cmd_In_Sent									(13)
#define Seventh_Cmd_Sent									(14)
#define Final_Cmd_Sent										(15)
#define Reading_First_Nibble								(16)
#define Reading_Second_Nibble								(17)
#define Reading_Second_Nibble_Done							(18)
#define Sending_Character_Location							(19)
#define CMD_Sending											(20)
#define CMD_Sent											(21)
#define Sending_First_Nibble_E								(22)
#define Sending_Second_Nibble_E								(23)
#define Sending_Second_Nibble_SET_E							(24)
#define Sending_Second_Nibble_SET_ENABLE					(25)

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/**
 * @brief: This function initializes a LCD.
 *
 * @param [in]  None.
 *
 * @return function error state.
 */


LCD_ERROR_state_t LCD_init(void)
{
	/*function starting*/
	uint8_t ErrRetVal = OperationStarted;
	/*setting the functions state*/
	uint8_t static LCD_State = OperationStarted;

	uint8_t LCD_SendCommandRetVal = OperationStarted;
#if (DATA_BITS_MODE == 4)
	switch (LCD_State)
	{
	case OperationStarted:
		/*TIMER Function Configuration */
		TIMER_VidInit(&timer_config,0,250);
 		LCD_CTRL_PORT_DIR |= (1<<E) | (1<<RS) | (1<<RW); /* Configure the control pins(E,RS,RW) as output pins */

		/*To Execute The Timer To Put Initial Value In Clock  */
		LCD_DATA_PORT_DIR |= 0xF0; /* Configure the highest 4 bits of the data port as output pins */
		/*set status of the function*/
		LCD_State = LCD_Pin_Initializing;
		break;
	case LCD_Pin_Initializing:
		/*if timer delay function finished correctly Start the initialization sequence*/
		LCD_State = LCD_Start_Initialization;
		break;
	case LCD_Start_Initialization:
		LCD_SendCommandRetVal = LCD_SendCommand(FOUR_BITS_DATA_MODE);
		if(LCD_SendCommandRetVal == OperationSuccess)
		{
			LCD_State = First_Cmd_Sent;
		}
		break;
	case First_Cmd_Sent:
		LCD_SendCommandRetVal = LCD_SendCommand(TWO_LINE_LCD_Four_BIT_MODE);
		if(LCD_SendCommandRetVal == OperationSuccess)
		{
			LCD_State = Second_Cmd_Sent;

		}
		break;
	case Second_Cmd_Sent:
		LCD_SendCommandRetVal = LCD_SendCommand(CURSOR_OFF);
		if(LCD_SendCommandRetVal == OperationSuccess)
		{
			LCD_State = Third_Cmd_Sent;

		}
		break;
	case Third_Cmd_Sent:
		LCD_SendCommandRetVal = LCD_SendCommand(CLEAR_COMMAND);
		if(LCD_SendCommandRetVal == OperationSuccess)
		{
			LCD_State = OperationStarted;
			ErrRetVal = OperationSuccess;
		}
		break;
	default:
		ErrRetVal = OperationFail;
	}
#endif

	return ErrRetVal;
}


/**
 * @brief: This function sends a command to LCD.
 *
 * @param [in]  Data  -  Data command to send to LCD.
 *
 * @return function error state.
 */


LCD_ERROR_state_t LCD_SendCommand(uint8_t command)
{
	/*function starting*/
	uint8_t ErrRetVal = OperationStarted;
	/*setting the functions state*/
	uint8_t static Command_State = OperationStarted;
	/*declaring a variable for the timer return*/
#if (DATA_BITS_MODE == 4)
	switch(Command_State)
	{
	case OperationStarted:
		CLEAR_BIT(LCD_CTRL_PORT,RS); /* Instruction Mode RS=0 */
		CLEAR_BIT(LCD_CTRL_PORT,RW); /* write data to LCD so RW=0 */
		Command_State = Sending_First_Nibble_E;
		break;
	case Sending_First_Nibble_E:
		if(TimerRetVal1==NULL_PTR)
		{
			TimerRetVal1=TIMER_Get_Status(&timer_config,1);
		}
		if(*TimerRetVal1==2)
		{
			SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
			*TimerRetVal1=0;
			TimerRetVal1=NULL_PTR;
			Command_State = Sending_First_Nibble;
		}
		break;
	case Sending_First_Nibble:
		/*start timer delay in background*/
		if(TimerRetVal1==NULL_PTR)
		{
			TimerRetVal1=TIMER_Get_Status(&timer_config,1);
		}
		if(*TimerRetVal1==2)
		{
			/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command & 0xF0);
			*TimerRetVal1=0;
			TimerRetVal1=NULL_PTR;
			Command_State = Sending_Second_Nibble_E;
		}
		break;
	case Sending_Second_Nibble_E:
		/*start timer delay in background*/
		if(TimerRetVal1==NULL_PTR)
		{
			TimerRetVal1=TIMER_Get_Status(&timer_config,1);
		}
		if(*TimerRetVal1==2)
		{
			/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
			CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
			*TimerRetVal1=0;
			TimerRetVal1=NULL_PTR;
			Command_State = Sending_Second_Nibble_SET_E;
		}
		break;
	case Sending_Second_Nibble_SET_E:
		/*start timer delay in background*/
		if(TimerRetVal1==NULL_PTR)
		{
			TimerRetVal1=TIMER_Get_Status(&timer_config,1);
		}
		if(*TimerRetVal1==2)
		{
			/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
			SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
			*TimerRetVal1=0;
			TimerRetVal1=NULL_PTR;
			Command_State = Sending_Second_Nibble;
		}
		break;
	case Sending_Second_Nibble:
		/*start timer delay in background*/
		if(TimerRetVal1==NULL_PTR)
		{
			TimerRetVal1=TIMER_Get_Status(&timer_config,1);
		}
		if(*TimerRetVal1==2)
		{
			/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((command & 0x0F) << 4);
			*TimerRetVal1=0;
			TimerRetVal1=NULL_PTR;
			Command_State = Sending_Second_Nibble_SET_ENABLE;
		}
		break;
	case Sending_Second_Nibble_SET_ENABLE:
		if(TimerRetVal1==NULL_PTR)
		{
			TimerRetVal1=TIMER_Get_Status(&timer_config,1);
		}
		if(*TimerRetVal1==2)
		{
			/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
			CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
			*TimerRetVal1=0;
			TimerRetVal1=NULL_PTR;
			Command_State = CMD_Sending;
		}
		break;
	case CMD_Sending:
		if(TimerRetVal1 == NULL_PTR)
		{
			/*reset the function's state*/
			Command_State = OperationStarted;
			/*process finished successfully*/
			ErrRetVal = OperationSuccess;
		}
		break;
	default:
		ErrRetVal = OperationFail;
	}
#endif
	/*return from function*/
	return ErrRetVal;
}
/**
 * @brief: This function Prints a character to LCD.
 *
 * @param [in]  Data     -  Character to send to LCD.
 *
 * @return function error state.
 */
LCD_ERROR_state_t LCD_displayCharacter(uint8_t command)
{
	/*function starting*/
	uint8_t ErrRetVal = OperationStarted;
	/*setting the functions state*/
	uint8_t static Data_State = OperationStarted;
	/*declaring a variable for the timer return*/
#if (DATA_BITS_MODE == 4)
	switch(Data_State)
	{
	case OperationStarted:
		SET_BIT(LCD_CTRL_PORT,RS); /* Instruction Mode RS=0 */
		CLEAR_BIT(LCD_CTRL_PORT,RW); /* write data to LCD so RW=0 */
		Data_State = Sending_First_Nibble_E;
		break;
	case Sending_First_Nibble_E:
		if(TimerRetVal1==NULL_PTR)
		{
			TimerRetVal1=TIMER_Get_Status(&timer_config,1);
		}
		if(*TimerRetVal1==2)
		{
			SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
			*TimerRetVal1=0;
			TimerRetVal1=NULL_PTR;
			Data_State = Sending_First_Nibble;
		}
		break;
	case Sending_First_Nibble:
		/*start timer delay in background*/
		if(TimerRetVal1==NULL_PTR)
		{
			TimerRetVal1=TIMER_Get_Status(&timer_config,1);
		}
		if(*TimerRetVal1==2)
		{
			/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command & 0xF0);
			*TimerRetVal1=0;
			TimerRetVal1=NULL_PTR;
			Data_State = Sending_Second_Nibble_E;
		}
		break;
	case Sending_Second_Nibble_E:
		/*start timer delay in background*/
		if(TimerRetVal1==NULL_PTR)
		{
			TimerRetVal1=TIMER_Get_Status(&timer_config,1);
		}
		if(*TimerRetVal1==2)
		{
			/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
			CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
			*TimerRetVal1=0;
			TimerRetVal1=NULL_PTR;
			Data_State = Sending_Second_Nibble_SET_E;
		}
		break;
	case Sending_Second_Nibble_SET_E:
		/*start timer delay in background*/
		if(TimerRetVal1==NULL_PTR)
		{
			TimerRetVal1=TIMER_Get_Status(&timer_config,1);
		}
		if(*TimerRetVal1==2)
		{
			/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
			SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
			*TimerRetVal1=0;
			TimerRetVal1=NULL_PTR;
			Data_State = Sending_Second_Nibble;
		}
		break;
	case Sending_Second_Nibble:
		/*start timer delay in background*/
		if(TimerRetVal1==NULL_PTR)
		{
			TimerRetVal1=TIMER_Get_Status(&timer_config,1);
		}
		if(*TimerRetVal1==2)
		{
			/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((command & 0x0F) << 4);
			*TimerRetVal1=0;
			TimerRetVal1=NULL_PTR;
			Data_State = Sending_Second_Nibble_SET_ENABLE;
		}
		break;
	case Sending_Second_Nibble_SET_ENABLE:
		if(TimerRetVal1==NULL_PTR)
		{
			TimerRetVal1=TIMER_Get_Status(&timer_config,1);
		}
		if(*TimerRetVal1==2)
		{
			/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
			CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
			*TimerRetVal1=0;
			TimerRetVal1=NULL_PTR;
			Data_State = CMD_Sending;
		}
		break;
	case CMD_Sending:
		if(TimerRetVal1 == NULL_PTR)
		{
			/*reset the function's state*/
			Data_State = OperationStarted;
			/*process finished successfully*/
			ErrRetVal = OperationSuccess;
		}
		break;
	default:
		break;
	}
#endif
	/*return from function*/
	return ErrRetVal;
}

/**
 * @brief: This function Prints a string on LCD.
 *
 * @param [in]  Str     -  String to send to LCD.
 *
 * @return function error state.
 */
LCD_ERROR_state_t  LCD_displayString(const char *Str)
{
	if(NULL_PTR == Str)
	{
		return E_LCD_NULL_PTR;
	}
	uint8_t i = 0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
	/***************** Another Method ***********************
	while((*Str) != '\0')
	{
		LCD_displayCharacter(*Str);
		Str++;
	}
	 *********************************************************/
	return E_LCD_SUCCESS;
}
/**
 * @brief: This function Sets LCD cursor on a specific position.
 *
 * @param [in]  Row      -  Row position.
 * @param [in]  Col      -  Column position.
 *
 * @return function error state.
 */
LCD_ERROR_state_t  LCD_goToRowColumn(uint8_t row,uint8_t col)
{
	uint8_t Address=0;

	/* first of all calculate the required address */
	switch(row)
	{
	case 0:
		Address=col;
		break;
	case 1:
		Address=col+0x40;
		break;
	case 2:
		Address=col+0x10;
		break;
	case 3:
		Address=col+0x50;
		break;
	}
	/* to write to a specific address in the LCD
	 * we need to apply the corresponding command 0b10000000+Address */
	LCD_SendCommand(Address | SET_CURSOR_LOCATION);

	return E_LCD_SUCCESS;
}
/**
 * @brief: This function Sets LCD cursor on a specific position and
 * Prints a string on LCD.
 *
 * @param [in]  Row      -  Row position.
 * @param [in]  Col      -  Column position.
 * @param [in]  Str      -  String to send to LCD.
 *
 * @return function error state.
 */
LCD_ERROR_state_t LCD_displayStringRowColumn(uint8_t row,uint8_t col,const char *Str)
{
	LCD_goToRowColumn(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
	return E_LCD_SUCCESS;

}

/**
 * @brief: This function Prints a Number on LCD.
 *
 * @param [in]  a-Number     -  Number to send to LCD.
 *
 * @return function error state.
 */
LCD_ERROR_state_t LCD_VidWriteNumber (uint64_t a_Number)
{
	uint64_t reversed=1;
	if(a_Number==0)
	{
		LCD_displayCharacter('0');
	}
	while(a_Number != 0)
	{
		reversed = (reversed * 10)+(a_Number%10);

		a_Number/=10;
	}
	while(reversed != 1)
	{
		LCD_displayCharacter((reversed%10)+48);
		reversed /= 10;
	}
	return E_LCD_SUCCESS;
}



void LCD_clearScreen(void)
{
	LCD_SendCommand(CLEAR_COMMAND); //clear display
}
