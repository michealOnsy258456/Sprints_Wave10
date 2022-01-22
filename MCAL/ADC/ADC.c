/*
 * ADC.c
 *
 *  Created on: Jan 19, 2022
 *      Author: Micheal-Onsy
 */

#include "ADC.h"
/*- LOCAL MACROS
------------------------------------------*/
#define INIT         (uint8_t)(1)
#define NOT_INIT     (uint8_t)(0)

/*- GLOBAL STATIC VARIABLES
-------------------------------*/

static void (*g_Callback)(void);
volatile uint16_t *g_adcResult = 0;


static uint8_t gu8_IsInit = NOT_INIT;

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
extern const uint8_t ADC_REFERENCE_SELECTION;
extern const uint8_t ADC_CONTROL_MASK;

ADC_ERROR_state_t ADC_Init(void)
{
   /* making sure ADC was initialized before calling this function */
   if(INIT == gu8_IsInit)
   {
      return E_ADC_INIT_BEFORE;
   }

   /* Set VRef Selection */
   ADMUX |= ADC_REFERENCE_SELECTION;

   /* Configure ADC */
   ADCSRA |= ADC_CONTROL_MASK;

   /* Set Driver State to Initialized */
   gu8_IsInit = INIT;

   /* return success status */
   return E_ADC_SUCCESS;
}
/**
* @brief: This function read the ADC pin value.
*
* @param [in]  ADC_CH   -  ADC channel number.
* @param [in]  Data     -  pointer to where to store ADC readings.
*
* @return function error state.
*/
ADC_ERROR_state_t ADC_Read(uint8_t ADC_CH, uint16_t * Data)
{
   /* making sure ADC was initialized before calling this function */
   if(NOT_INIT == gu8_IsInit)
   {
      return E_ADC_NOT_INIT;
   }
   /* making sure an initialized pointer is sent to the function */
   else if(NULL_PTR == Data)
   {
      return E_ADC_NULL_PTR;
   }
   else if(ADC_CH_7 < ADC_CH)
   {
      return E_ADC_INVALID_CH;
   }

   /* Select the required ADC channel */
   ADMUX |= (ADC_CH & 0x1F);

   /* Start Conversion */
   ADCSRA |= ADC_START_CONVERSION;

   /* Wait for Interrupt Flag */
   while(!(ADCSRA & ADC_INTERRUPT_FLAG));

   /* clear interrupt flag */
   ADCSRA |= ADC_INTERRUPT_FLAG;

   /* return ADC conversion data */
   *Data = (ADCL);
   *Data += (ADCH << 8);

   /* return success status */
   return E_ADC_SUCCESS;
}

/**
* @brief: This function enables ADC interrupt.
*
* @return function error state.
*/
ADC_ERROR_state_t ADC_EnableInterrupt(void)
{
   /* making sure ADC was initialized before calling this function */
   if(NOT_INIT == gu8_IsInit)
   {
      return E_ADC_NOT_INIT;
   }

   /* Enable Interrupt */
   ADCSRA |= (ADC_INTERRUPT_EN);

   /* return success status */
   return E_ADC_SUCCESS;
}

/**
* @brief: This function disables ADC interrupt.
*
* @return function error state.
*/
ADC_ERROR_state_t ADC_DisableInterrupt(void)
{
   /* making sure ADC was initialized before calling this function */
   if(NOT_INIT == gu8_IsInit)
   {
      return E_ADC_NOT_INIT;
   }

   /* Disable Interrupt */
   ADCSRA &= ~(ADC_INTERRUPT_EN);

   /* return success status */
   return E_ADC_SUCCESS;
}

/**
* @brief: This function sets Callback Function.
*
* @param [in]  Callback   -  Pointer to a function.
*
* @return function error state.
*/
ADC_ERROR_state_t ADC_SetCallback(void (*Callback)(void))
{
   /* making sure ADC was initialized before calling this function */
   if(NOT_INIT == gu8_IsInit)
   {
      return E_ADC_NOT_INIT;
   }
   /* making sure an initialized pointer is sent to the function */
   else if(NULL_PTR == Callback)
   {
      return E_ADC_NULL_PTR;
   }

   /* set callback function */
   g_Callback = Callback;

   /* return success status */
   return E_ADC_SUCCESS;
}


ISR(ADC_vect)
{
	/* Read ADC Data after conversion complete */
	*g_adcResult = (ADCL);
	*g_adcResult += (ADCH << 8);
}
