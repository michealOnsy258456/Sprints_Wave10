/*
 * ADC.h
 *
 *  Created on: Jan 19, 2022
 *      Author: Micheal-Onsy
 */

#ifndef MCAL_ADC_ADC_H_
#define MCAL_ADC_ADC_H_

#include "ADC_Config.h"
#include "Std_type.h"
#include "Register.h"

/*- PRIMITIVE TYPES ----------------------------------------*/
typedef uint8_t ADC_ERROR_state_t;
extern volatile uint16_t * g_adcResult;


/*- ERRORS DEFINITIONS--------------------------------------*/

#define           E_ADC_SUCCESS                    (ADC_ERROR_state_t)( 0 )
#define           E_ADC_NULL_PTR                   (ADC_ERROR_state_t)( 1 )
#define           E_ADC_INVALID_CH                 (ADC_ERROR_state_t)( 2 )
#define           E_ADC_INIT_BEFORE                (ADC_ERROR_state_t)( 3 )
#define           E_ADC_NOT_INIT                   (ADC_ERROR_state_t)( 4 )

/*- FUNCTION DECLARATIONS ----------------------------------*/

/* Initialize ADC */
ADC_ERROR_state_t ADC_Init(void);

/* Read ADC Channel */
ADC_ERROR_state_t ADC_Read(uint8_t ADC_CH, uint16_t * Data);

/* Enable Interrupt */
ADC_ERROR_state_t ADC_EnableInterrupt(void);

/* Disable Interrupt */
ADC_ERROR_state_t ADC_DisableInterrupt(void);

/* Set Callback Function */
ADC_ERROR_state_t ADC_SetCallback(void (*Callback)(void));


#endif /* MCAL_ADC_ADC_H_ */
