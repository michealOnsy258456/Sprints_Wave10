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

#include "App.h"

/*******************************************************************************
 *                              Global Variables                               *
 *******************************************************************************/
TIM_Config tim_config = { TIMER_2, COMPARE, TIMER2_F_CLK_1024};
TIM_Config tim1_config = { TIMER_0, COMPARE, TIMER0_F_CLK_8};
/* Global array to store the data as a buffer */
uint8_t gu8_arr[250]={0};
/* Global variable to State Application */
uint8_t LCD_Flag = FALSE , Update_Flag = FALSE ;
uint8_t counter = 0;
uint8_t gu8_key = FALSE;	/* Global variable to store the key value */
uint8_t gu8_flag = NOT_PRESSED;	/* Global variable to store the status of the keypad */

uint8_t Check_Data = 0 , LCD_PrintStatus=0;



/*******************************************************************************
 *                           Functions Definitions                             *
 *******************************************************************************/

/*******************************************************************************
 * [Function Name]: App_init
 *
 * [Description]: 	Function to Initialize the application to test keypad Driver
 *
 * [Args]:			None
 *
 * [in]			  	None
 *
 * [out]		  	None
 *
 * [in/out]		 	None
 *
 * [Returns]:       None
 *******************************************************************************/
void App_init_Without_Looping(void)
{
	DIO_setPortDirection(PORTc,DIO_u8_OUTPUT_PORT);

	KEYPAD_Init();	/* KEYPAD Initialization */
}

/*******************************************************************************
 * [Function Name]: App_Update
 *
 * [Description]: 	Function to update the state of the application
 *
 * [Args]:			None
 *
 * [in]			  	None
 *
 * [out]		  	None
 *
 * [in/out]		 	None
 *
 * [Returns]:       None
 *******************************************************************************/
void App_Update(void)
{
	uint8_t Flag=0;
	static uint8_t Last_Data=0;
	static uint8_t New_Data=0;
	TIMER_Get_Status(&tim_config,Flag);
	TIMER_Get_Status(&tim1_config,Flag);

	gu8_flag = KEYPAD_getStatus(&gu8_key);/* get the pressed key number */
	New_Data=data_return();

	/* Check if the Last daata Equal New data */

	if (Last_Data != New_Data)
	{
		Check_Data=1;
	}
	if(Check_Data==1)
	{
		if(LCD_Flag == TRUE)
		{
			if(Update_Flag==FALSE)
			{
				LCD_PrintStatus = LCD_displayCharacter(New_Data+'0');
				if (LCD_PrintStatus == OperationSuccess)
				{
					DIO_writePortValue(PORTc,New_Data);
					Last_Data=New_Data;
					Check_Data=0;
				}
			}
		}

	}

}
/*******************************************************************************
 * [Function Name]: App_init
 *
 * [Description]: 	Function to Initialize the application to test keypad Driver
 *
 * [Args]:			None
 *
 * [in]			  	None
 *
 * [out]		  	None
 *
 * [in/out]		 	None
 *
 * [Returns]:       None
 *******************************************************************************/
void App_init(void)
{

	if (LCD_Flag == FALSE && (LCD_init()==OperationSuccess))
	{
		LCD_Flag=TRUE;
	}
	TIMER_Get_Status(&tim1_config,0);

}
