/*
 * ADC_Config.c
 *
 *  Created on: Jan 19, 2022
 *      Author: Micheal-Onsy
 */

#include "ADC_Config.h"
#include "ADC.h"

const uint8_t ADC_REFERENCE_SELECTION = (ADC_VREF_AVCC);
const uint8_t ADC_CONTROL_MASK = (ADC_ENABLE | ADC_PRESCALAR_2);
