/*
 * Register.h
 *
 *  Created on: Jan 19, 2022
 *      Author: Micheal-Onsy
 */

#ifndef LIBRARY_REGISTER_H_
#define LIBRARY_REGISTER_H_


/*- PORTA REGISTERS-----------------------------------------*/
#define  PORTA      	(*((volatile uint8_t *) (0x3B)))
#define  DDRA       	(*((volatile uint8_t *) (0x3A)))
#define  PINA       	(*((volatile uint8_t *) (0x39)))

/*- PORTB REGISTERS-----------------------------------------*/
#define  PORTB      	(*((volatile uint8_t *) (0x38)))
#define  DDRB       	(*((volatile uint8_t *) (0x37)))
#define  PINB       	(*((volatile uint8_t *) (0x36)))

/*- PORTC REGISTERS-----------------------------------------*/
#define  PORTC      	(*((volatile uint8_t *) (0x35)))
#define  DDRC       	(*((volatile uint8_t *) (0x34)))
#define  PINC       	(*((volatile uint8_t *) (0x33)))

/*- PORTD REGISTERS-----------------------------------------*/
#define  PORTD      	(*((volatile uint8_t *) (0x32)))
#define  DDRD       	(*((volatile uint8_t *) (0x31)))
#define  PIND       	(*((volatile uint8_t *) (0x30)))

/*- ADC REGISTERS-----------------------------------------*/

#define  ADCL       	(*((volatile uint8_t *) (0x24)))
#define  ADCH  			(*((volatile uint8_t *) (0x25)))
#define  ADMUX      	(*((volatile uint8_t *) (0x27)))
#define  ADCSRA     	(*((volatile uint8_t *) (0x26)))
#define  SFIOR      	(*((volatile uint8_t *) (0x50)))

/*- UART REGISTERS-----------------------------------------*/


#define UDR       		(*((volatile uint8_t *) (0x2C)))
#define UCSRC     		(*((volatile uint8_t *) (0x40)))
#define UBRRH     		(*((volatile uint8_t *) (0x40)))
#define UCSRA     		(*((volatile uint8_t *) (0x2B)))
#define UCSRB     		(*((volatile uint8_t *) (0x2A)))
#define UBRRL     		(*((volatile uint8_t *) (0x29)))

/*- SPI REGISTERS-----------------------------------------*/
#define SPCR     		(*((volatile uint8_t *) (0x2D)))
#define SPSR     		(*((volatile uint8_t *) (0x2E)))
#define SPDR     		(*((volatile uint8_t *) (0x2F)))

/*- TWI REGISTERS-----------------------------------------*/
#define  TWDR           (*((volatile uint8_t *) (0x23)))
#define  TWAR      		(*((volatile uint8_t *) (0x22)))
#define  TWSR         	(*((volatile uint8_t *) (0x21)))
#define  TWBR       	(*((volatile uint8_t *) (0x20)))
#define  TWCR        	(*((volatile uint8_t *) (0x56)))

#endif /* LIBRARY_REGISTER_H_ */
