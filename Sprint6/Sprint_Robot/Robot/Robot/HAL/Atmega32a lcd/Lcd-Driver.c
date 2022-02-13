 /*
 * Lcd_Driver.c
 *
 * Created: 4/12/2021 3:14:06 PM
 * Author : Ahmed_Ayman
 */
#include "LCD-Driver.h"


/* start position for x & y location as described in data sheet*/ 


/*
 * brief  : this function used to send Data to LCD in 4 bit form 
 * param. : data the specific byte that you want to send to LCD 
 * return : void 
 */
static void LCD_Send_4BitData(uint8_t data);

/*
 * brief  : this function used to set enable bit in LCD
 * return : void 
 */
static void LCD_Triger_Enable(void);


/*
 * brief  : this function used to set enable bit in LCD
 * return : void 
 */


static void LCD_Triger_Enable(void)
{
	
	HAL_GPIO_WRITEPIN(LcdBitSelect.LcdBits[LCD_BIT_E_PIN].Port,LcdBitSelect.LcdBits[LCD_BIT_E_PIN].Pin,GPIO_PIN_SET);  // set enable pin
	_delay_us(1);
	HAL_GPIO_WRITEPIN(LcdBitSelect.LcdBits[LCD_BIT_E_PIN].Port,LcdBitSelect.LcdBits[LCD_BIT_E_PIN].Pin,GPIO_PIN_RESET);  // set enable pin
	_delay_ms(2);	
	
} /* END_FUN LCD_Triger_Enable()*/


/*
 * brief  : this function used to send Data to LCD in 4 bit form 
 * param. : data the specific byte that you want to send to LCD 
 * return : void 
 */
static void LCD_Send_4BitData(uint8_t data)
{
	
		for(int i =3 ; i < 7 ;i++)																			
		HAL_GPIO_WRITEPIN(LcdBitSelect.LcdBits[i].Port,LcdBitSelect.LcdBits[i].Pin,((1<<(i+1))&(data))>>(i+1));	/* set the high nibble */
		LCD_Triger_Enable();
		for(int i =3 ; i < 7 ;i++)
		HAL_GPIO_WRITEPIN(LcdBitSelect.LcdBits[i].Port,LcdBitSelect.LcdBits[i].Pin,((1<<(i-3))&(data))>>(i-3));	/* set the high nibble */
		LCD_Triger_Enable();


} /* END_FUN LCD_Send_4BitData()*/



/*
 * brief  : this function used to send an character to LCD with the current location 
 * param. : Character the specific character to send to LCD 
 * return : void 
 */ 
LCD_Status_t LCD_Send_Character_CurrLoc(uint8_t character)
{
	HAL_GPIO_WRITEPIN(LcdBitSelect.LcdBits[LCD_BIT_RS_PIN].Port,LcdBitSelect.LcdBits[LCD_BIT_RS_PIN].Pin,GPIO_PIN_SET);  // set enable pin
	HAL_GPIO_WRITEPIN(LcdBitSelect.LcdBits[LCD_BIT_RW_PIN].Port,LcdBitSelect.LcdBits[LCD_BIT_RW_PIN].Pin,GPIO_PIN_RESET);  // set enable pin

	LCD_Send_4BitData(character);
	
		return LCD_OK ;
} /* END_FUN LCD_Send_Character_CurrLoc()*/




/*
 * brief  : this function used to send command to LCD  
 * param. : command the specific command to send to LCD chose one of @ LCD_COMMANED_ 
 * return : void 
 */
LCD_Status_t LCD_Send_Command(uint8_t command)
{
	
	HAL_GPIO_WRITEPIN(LcdBitSelect.LcdBits[LCD_BIT_RS_PIN].Port,LcdBitSelect.LcdBits[LCD_BIT_RS_PIN].Pin,GPIO_PIN_RESET);  // set enable pin		
	HAL_GPIO_WRITEPIN(LcdBitSelect.LcdBits[LCD_BIT_RW_PIN].Port,LcdBitSelect.LcdBits[LCD_BIT_RW_PIN].Pin,GPIO_PIN_RESET);  // set enable pin
	LCD_Send_4BitData(command);
	
	
		return LCD_OK ;
} /* END_FUN LCD_Send_Command()*/




/*
 * brief  : this function used to send an character to LCD with the chosen location 
 * param. :  y  is specify the new Y axises
 * param. :  x  is specify the new X axises
 * param. : character the specific character to send to LCD 
 * return : void 
 */
LCD_Status_t LCD_Send_Character_WithLoc(uint8_t y,uint8_t x,uint8_t character)
{
	
	LCD_Goto_Location(y,x);
	HAL_GPIO_WRITEPIN(LcdBitSelect.LcdBits[LCD_BIT_RS_PIN].Port,LcdBitSelect.LcdBits[LCD_BIT_RS_PIN].Pin,GPIO_PIN_SET);  // set enable pin
	HAL_GPIO_WRITEPIN(LcdBitSelect.LcdBits[LCD_BIT_RW_PIN].Port,LcdBitSelect.LcdBits[LCD_BIT_RW_PIN].Pin,GPIO_PIN_RESET);  // set enable pin
	LCD_Send_4BitData(character);
	
	
		return LCD_OK ;
} /* END_FUN LCD_Send_Character_WithLoc()*/





/*
 * brief  : this function used to send an string to LCD with the current location 
 * param. : Character the specific character to send to LCD 
 * return : void 
 */
LCD_Status_t LCD_Send_String_CurrLoc(uint8_t *string)
{
	while (*string != 0)
	{
		LCD_Send_Character_CurrLoc(*string++);

	}
	
	
	return LCD_OK ;
} /* END_FUN LCD_Send_String_CurrLoc()*/




/*
 * brief  : this function used to modify the current cursor location 
 * param. :  y  is specify the new Y axises
 * param. :  x  is specify the new X axises
 * return : void 
 */
LCD_Status_t LCD_Goto_Location(uint8_t y , uint8_t x)
{
	uint8_t column_position [2] = {0x80,0xc0};
	LCD_Send_Command(column_position[y-1]+(x-1));


	return LCD_OK ;	
} /* END_FUN LCD_Goto_Location()*/




/*
 * brief  : this function used to initialize (GPIO &LCD) 
 * return : void 
 */ 
LCD_Status_t LCD_Initializaion(void)
{
	GPIO_InitTypeDef LCD_GPIO_Handler ;
	
	
	_delay_ms(20);
	/* Set portB pin 1,2,3 as output */
	LCD_GPIO_Handler.mode = GPIO_MODE_OUTPUT ;
	LCD_GPIO_Handler.pull =GPIO_NOPULL ;
	
	
	
	
	for(int i =0 ; i < 7 ;i++)
	{
		LCD_GPIO_Handler.pin = LcdBitSelect.LcdBits[i].Pin ;
		  
		HAL_GPIO_Pin_Init(LcdBitSelect.LcdBits[i].Port,&LCD_GPIO_Handler);
	}

	/* LCD Initialization command*/
	LCD_Send_Command(0x33U);  
	LCD_Send_Command(0x32U);
	LCD_Send_Command(LCD_COMMANED2LINE_4_BIT_MODE);
	LCD_Send_Command(LCD_COMMANED_CLEAR_CURSOR_OFF);
	LCD_Send_Command(LCD_COMMANED_CLEAR_LCD);
	

	return LCD_OK ;
	
} /* END_FUN LCD_Initializaion()*/




/*
 * brief  : this function used to send an string to LCD with the chosen location 
 * param. :  y  is specify y axises location start from 1
 * param. :  x  is specify y axises location start from 1
 * param. : StringOfCharacters pointer to string that you want to display
 * return : void 
 */
LCD_Status_t LCD_Send_String_WithLoc(uint8_t y, uint8_t x, uint8_t * StringOfCharacters)
{
	LCD_Goto_Location(y,x);
	while (*StringOfCharacters != 0)
	{
		LCD_Send_Character_CurrLoc(*StringOfCharacters++);  
	}
	
	
	return LCD_OK ;
} /* END_FUN Send_A_String_WithLoc()*/





/*
 * brief  : this function used to send an floating point number to LCD with the chosen location 
 * param. :  y  is specify y axises location start from 1 
 * param. :  x  is specify y axises location start from 1
 * param. : IntegerToDisplay this is the integer value that you want to display
 * return : void 
 */
LCD_Status_t LCD_Send_Float_Withloc(uint8_t y, uint8_t x ,  float number )
{
	LCD_Goto_Location(y,x);
	
	uint16_t intValue = (uint16_t)number;                    /* calculate the int value */
	float diffValue = (number - (float)intValue);              
	uint16_t decimalValue = (uint16_t)(diffValue * pow(10,2));  /* calculate the float value */
	
	
	LCD_Send_Integer_CurrLoc(intValue,5);
	LCD_Send_Character_CurrLoc('.');
	LCD_Send_Integer_CurrLoc(decimalValue,5);
	
	
		return LCD_OK ;
} /* END_FUN LCD_Send_Float_Withloc()*/





/*
 * brief  : this function used to send an 16 bit integer to LCD with the current location 
 * param. : IntegerToDisplay this is the integer value that you want to display
 * param. : NumberOfDigits number of digits of the integer number that you want to display
 * return : void 
 */
LCD_Status_t LCD_Send_Integer_CurrLoc(uint16_t IntegerToDisplay, uint8_t NumberOfDigits)
{
		uint8_t StringToDisplay[NumberOfDigits];   /* create array with required size */ 
		itoa(IntegerToDisplay,(char *)StringToDisplay,10); /* convert from int num. to char num. */
		LCD_Send_String_CurrLoc(StringToDisplay);  /* print char array on the screen */
	
	
		return LCD_OK ;
} /* END_FUN LCD_Send_Integer_CurrLoc()*/




/*
 * brief  : this function used to send an 16 bit integer to LCD with the chosen location 
 * param. :  y  is specify y axises location start from 1
 * param. :  x  is specify y axises location start from 1
 * param. : IntegerToDisplay this is the integer value that you want to display
 * param. : NumberOfDigits number of digits of the integer number that you want to display
 * return : void 
 */
LCD_Status_t LCD_Send_Integer_WithLoc(uint8_t y, uint8_t x, uint16_t IntegerToDisplay, uint8_t NumberOfDigits)
{
	uint8_t StringToDisplay[NumberOfDigits];   /* create array with required size */
	itoa(IntegerToDisplay,(char *)StringToDisplay,10); /* convert from int num. to char num. */
	for (uint16_t i=0;i<NumberOfDigits;i++)
		LCD_Send_Character_CurrLoc(' ');
		
	LCD_Send_String_WithLoc(y,x,StringToDisplay);
	
	
	
		return LCD_OK ;
} /* END_FUN LCD_Send_Integer_WithLoc()*/

