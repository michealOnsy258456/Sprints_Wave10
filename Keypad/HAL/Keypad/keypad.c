/******************************************************************************
 *
 * [MODULE]: KEYPAD
 *
 * [FILE NAME]: keypad.c
 *
 * [DESCRIPTION]: Source file for the Keypad driver
 *
 * [AUTHOR]: Micheal Onsy
 *
 *******************************************************************************/

#include "keypad.h"

/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/

/* Global variable to store the debounce_Status modified in the ISR */
volatile static uint8_t debounce_Status = FALSE;
TIM_Config timer1_config = { TIMER_2, COMPARE, TIMER2_F_CLK_1024};
uint8_t * LCDRetVal = NULL_PTR ;
uint8_t  Data_Store = 0 ;
uint8_t Flag=0;

/*******************************************************************************
 *                      Functions Prototypes(Private)                          *
 *******************************************************************************/

static ERROR_STATE_t KEYPAD_getPressedKey(uint8_t * au8_data);

#if (N_col == 3)
/*
 * Description: Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x3 keypad
 */
static uint8_t KeyPad_4x3_adjustKeyNumber(uint8_t button_number);
#elif (N_col == 4)
/*
 * Description: Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x4 keypad
 */
static uint8_t KeyPad_4x4_adjustKeyNumber(uint8 button_number);
#endif

/*******************************************************************************
 *                      Interrupt Service Routines                             *
 *******************************************************************************/

void KEYPAD_CheckDebounce(void)
{
	debounce_Status = TRUE;	/* Rise the denounce flag */

}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*********************************************************************************
 * @brief: This function initializes a KEYPAD_Init.
 *
 * @param [in]  None.
 *
 * @return function error state.
*
 * Description: Function to Initialize the KEYPAD
 ********************************************************************************/
ERROR_STATE_t KEYPAD_Init(void)
{
	/* Local variable to store the counter value */
	uint8_t au8_counter;

	/* Timer configurations */

	/* Timer driver initialization */
	TIMER_VidInit(&timer1_config,0,250);

	/* Function to be called when the interrupt is fired
	TIMER_setCallBack(KEYPAD_CheckDebounce, TIMER_1);
	 */
	/* Set columns pins to output initially High */
	for(au8_counter = 0; au8_counter < N_col; au8_counter++)
	{
		DIO_setPinDirection(KEYPAD_PORT, (KEYPAD_COL_PIN | au8_counter), DIO_u8_OUTPUT);
		DIO_writePinValue(KEYPAD_PORT, (KEYPAD_COL_PIN | au8_counter), DIO_u8_HIGH);
	}

	/* Set rows pins to input and set pull up resistors */
	for(au8_counter = 0; au8_counter < N_row; au8_counter++)
	{
		DIO_setPinDirection(KEYPAD_PORT, (KEYPAD_ROW_PIN | au8_counter), DIO_u8_INPUT);
		DIO_writePinValue(KEYPAD_PORT, (KEYPAD_ROW_PIN | au8_counter), DIO_u8_HIGH);
	}

	/* return success status */
	return E_OK;
}

/*********************************************************************************
 * @brief: This function initializes a KEYPAD_getStatus.
 *
 * @param [in]  Pointer (data).
 *
 * @return function error state.
*
 * Description: Function responsible for getting the status of the KEYPAD
 ********************************************************************************/
ERROR_STATE_t KEYPAD_getStatus(uint8_t * data)
{

	static uint8_t au8_keypad_Status = NOT_PRESSED;	/* Static variable to retain the state of the keypad */
	uint8_t au8_keypad_RetValue = NOT_PRESSED;	/* Local variable to return the keypad status */

	au8_keypad_RetValue = KEYPAD_getPressedKey(data);

	switch(au8_keypad_Status)
	{
	case NOT_PRESSED:
						if(au8_keypad_RetValue == PRESSED)
						{
							if(LCDRetVal==NULL_PTR)
							{
								TIMER_Start(TIMER2_F_CLK_8,TIMER_2 );	/* Start timer */
								LCDRetVal=TIMER_Get_Status(&timer1_config,2);
								Data_Store = *data ;
							}
							if(*LCDRetVal==2)
							{
								KEYPAD_CheckDebounce();
								*LCDRetVal=0;
								LCDRetVal=NULL_PTR;
								au8_keypad_Status = DEBOUNCING;	/* Update the KEYPAD state */
							}
						}
						au8_keypad_RetValue = NOT_PRESSED;	/* Update the return value of the keypad */
						break;

	case DEBOUNCING:	if(debounce_Status == TRUE)
						{
							debounce_Status = FALSE;	/* Reset the denounce flag */
							au8_keypad_Status = PRESSED;/* Update the KEYPAD state */
							au8_keypad_RetValue = PRESSED;/* Update the return value of the keypad */
						}
						break;

	case PRESSED:

						if(au8_keypad_RetValue == PRESSED)
						{
							/* Reset the state machine of the keypad only if the key is released */
							au8_keypad_Status = NOT_PRESSED;
						}
						au8_keypad_RetValue = Operation_Success;	/* Update the return value of the keypad */
						break;
						}

	return au8_keypad_RetValue;	/* Return the keypad status if it is (PRESSED, NOT PRESSED) */
}

/**
 * @brief: This function initializes a KEYPAD_getPressedKey.
 *
 * @param [in]  au8_data.
 *
 * @return function error state.
 */

ERROR_STATE_t KEYPAD_getPressedKey(uint8_t * au8_data)
{

	uint8_t au8_ColumnCounter;
	uint8_t au8_RowCounter;
	uint8_t au8_KeyStatus;
	uint8_t au8_Keyflag = NOT_PRESSED;

	/* Loops on every column */
	for(au8_ColumnCounter = 0; au8_ColumnCounter < N_col; au8_ColumnCounter++)
	{

		/* Set column value to low */
		DIO_writePinValue(KEYPAD_PORT, (KEYPAD_COL_PIN | au8_ColumnCounter) , DIO_u8_LOW);

		/* Loops on every row */
		for(au8_RowCounter = 0; au8_RowCounter < N_row; au8_RowCounter++)
		{
			/* Read row value */
			DIO_readPin(KEYPAD_PORT, (KEYPAD_ROW_PIN | au8_RowCounter), &au8_KeyStatus);
			/* Check if row is pressed */
			if(au8_KeyStatus == NOT_PRESSED)
			{
				*au8_data = KeyPad_4x3_adjustKeyNumber((au8_RowCounter * N_col) + (au8_ColumnCounter+1));
				/* Return column value to HIGH */
				au8_Keyflag = PRESSED;

			}
		}
		DIO_writePinValue(KEYPAD_PORT, (KEYPAD_COL_PIN | au8_ColumnCounter), DIO_u8_HIGH);
	}

	return au8_Keyflag;	/* Return the key flag if it is (PRESSED, NOT_PRESSED) */
}


#if (N_col == 3) 
/*********************************************************************************
 * @brief: This function initializes a KeyPad_4x3_adjustKeyNumber.
 *
 * @param [in]  au8_button_number.
 *
 * @return function error state.
*
 * Description: Function responsible for getting the actual number pressed
 ********************************************************************************/
static uint8_t KeyPad_4x3_adjustKeyNumber(uint8_t au8_button_number)
{
	switch(au8_button_number)
	{
	case 10: return '*'; /* ASCII Code of = */
	break;
	case 11: return 0;
	break;
	case 12: return '#'; /* ASCII Code of + */
	break;
	default: return au8_button_number;
	}
}

#elif (N_col == 4)
/*********************************************************************************
 * @brief: This function initializes a KeyPad_4x3_adjustKeyNumber.
 *
 * @param [in]  au8_button_number.
 *
 * @return function error state.
*
 * Description: Function responsible for getting the actual number pressed
 ********************************************************************************/
static uint8_t KeyPad_4x4_adjustKeyNumber(uint8_t au8_button_number)
{
	switch(au8_button_number)
	{
	case 1: return 7;
	break;
	case 2: return 8;
	break;
	case 3: return 9;
	break;
	case 4: return '%'; /* ASCII Code of % */
	break;
	case 5: return 4;
	break;
	case 6: return 5;
	break;
	case 7: return 6;
	break;
	case 8: return '*'; /* ASCII Code of '*' */
	break;
	case 9: return 1;
	break;
	case 10: return 2;
	break;
	case 11: return 3;
	break;
	case 12: return '-'; /* ASCII Code of '-' */
	break;
	case 13: return 13;  /* ASCII of Enter */
	break;
	case 14: return 0;
	break;
	case 15: return '='; /* ASCII Code of '=' */
	break;
	case 16: return '+'; /* ASCII Code of '+' */
	break;
	default: return au8_button_number;
	}
}

#endif


/*********************************************************************************
 * @brief: This function initializes a data_return.
 *
 * @param [in]  None.
 *
 * @return function Date .
*
 * Description: Function To send the data from Keypad
 ********************************************************************************/
uint8_t data_return(void)
{
	return Data_Store;
}
