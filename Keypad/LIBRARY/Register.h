/*
 * Register.h
 *
 *  Created on: Jan 2, 2022
 *      Author: Micheal-Onsy
 */

#ifndef REGISTER_H_
#define REGISTER_H_


#define PORTA      	(*((volatile uint8_t*) 0x3B	))
#define DDRA      	(*((volatile uint8_t*) 0x3A	))
#define PINA      	(*((volatile uint8_t*) 0x39	))

#define PORTB	    (*((volatile uint8_t*) 0x38	))
#define DDRB       	(*((volatile uint8_t*) 0x37	))
#define PINB      	(*((volatile uint8_t*) 0x36	))

#define PORTC	    (*((volatile uint8_t*) 0x35	))
#define DDRC       	(*((volatile uint8_t*) 0x34	))
#define PINC      	(*((volatile uint8_t*) 0x33	))

#define PORTD      	(*((volatile uint8_t*) 0x32 ))
#define DDRD       	(*((volatile uint8_t*) 0x31	))
#define PIND      	(*((volatile uint8_t*) 0x30	))

//Timer0 Registers
#define TCNT0     	(*((volatile uint8_t* ) 0x52 ))
#define OCR0      	(*((volatile uint8_t* ) 0x5C ))
#define TCCR0     	(*((volatile uint8_t* ) 0x53 ))

//Timer1 Registers
#define TCNT1     	(*((volatile uint16_t*) 0x4C ))
#define OCR1A     	(*((volatile uint16_t*) 0x4A ))
#define OCR1B     	(*((volatile uint16_t*) 0x48 ))
#define ICR1    	(*((volatile uint16_t*) 0x46 ))
#define TCCR1A    	(*((volatile uint8_t*)  0x4F ))
#define TCCR1B   	(*((volatile uint8_t*)  0x4E ))

//Timer2 Registers
#define TCCR2     	(*((volatile uint8_t*) 0x45 ))
#define TCNT2     	(*((volatile uint8_t*) 0x44 ))
#define OCR2      	(*((volatile uint8_t*) 0x43 ))
#define ASSR      	(*((volatile uint8_t*) 0x42 ))

//Timers interrupt registers
#define TIMSK     	(*((volatile uint8_t*) 0x59 ))
#define TIFR_R      (*((volatile uint8_t*) 0x58 ))



#endif /* REGISTER_H_ */
