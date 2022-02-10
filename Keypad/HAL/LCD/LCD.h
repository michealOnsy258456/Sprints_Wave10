/*
 * LCD.h
 *
 *  Created on: Dec 29, 2019
 *      Author: micheal_onsy
 */

#ifndef LCD_H_
#define LCD_H_
#include "../../LIBRARY/std_types.h"
#include "../../LIBRARY/Macros.h"
#include "../../LIBRARY/Register.h"
#include "../../MCAL/TIMER/TIMER.h"


/*- PRIMITIVE TYPES ----------------------------------------*/
typedef uint8_t LCD_ERROR_state_t;
/*- ERRORS DEFINITIONS--------------------------------------*/
/**
* @brief: This return value indicate that the function
* ran successfully and it returns no errors.
*/
#define           E_LCD_SUCCESS                    (LCD_ERROR_state_t)( 0 )
/**
* @brief: This return value indicate that a function got an
* uninitialized pointer.
*/
#define           E_LCD_NULL_PTR                   (LCD_ERROR_state_t)( 1 )
/**
* @brief: This return value indicate that a function got an
* invalid channel.
*/
#define           E_LCD_INVALID_CH                 (LCD_ERROR_state_t)( 2 )

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* LCD HW Pins */
#define DATA_BITS_MODE 4
#define UPPER_PORT_PINS
#define RS 1
#define RW 2
#define E  3
#define LCD_CTRL_PORT PORTB
#define LCD_CTRL_PORT_DIR DDRB
#define LCD_DATA_PORT PORTB
#define LCD_DATA_PORT_DIR DDRB

/* LCD Commands */
#define CLEAR_COMMAND 0x01
#define FOUR_BITS_DATA_MODE 0x02
#define LCD_Init_CMD_1	0x03
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define LCD_CURS_Position0			0x80
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80

/*functions return*/
#define OperationSuccess 											0
#define OperationFail 												1
#define OperationRunning											2
#define OperationStarted 											255


/*TIMER1 Configuration */
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
LCD_ERROR_state_t LCD_SendCommand(uint8_t command);
LCD_ERROR_state_t LCD_displayCharacter(uint8_t data);
LCD_ERROR_state_t LCD_displayString(const char *Str);
LCD_ERROR_state_t LCD_init(void);
LCD_ERROR_state_t LCD_displayStringRowColumn(uint8_t row,uint8_t col,const char *Str);
LCD_ERROR_state_t LCD_goToRowColumn(uint8_t row,uint8_t col);
LCD_ERROR_state_t LCD_VidWriteNumber (uint64_t a_Number);
void LCD_clearScreen(void);

#endif /* LCD_H_ */
