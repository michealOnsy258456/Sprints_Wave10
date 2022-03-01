/******************************************************************************
 *
 * [MODULE]: Register
 *
 * [FILE NAME]: Register.h
 *
 * [DESCRIPTION]: Header file for the Register
 *
 * [AUTHOR]: Micheal Onsy
 *
 *******************************************************************************/
#ifndef LIBRARY_REGISTER_H_
#define LIBRARY_REGISTER_H_

#define SREG_REG		(*((volatile uint8_t*) (0x5F)))
#define SPH_REG		    (*((volatile uint8_t*) (0x5E)))
#define SPL_REG			(*((volatile uint8_t*) (0x5D)))
#define OCR0_REG		(*((volatile uint8_t*) (0x5C)))
#define GICR_REG		(*((volatile uint8_t*) (0x5B)))
#define GIFR_REG		(*((volatile uint8_t*) (0x5A)))
#define TIMSK_REG		(*((volatile uint8_t*) (0x59)))
#define TIFR_REG		(*((volatile uint8_t*) (0x58)))
#define SPMCR_REG		(*((volatile uint8_t*) (0x57)))
#define TWCR_REG		(*((volatile uint8_t*) (0x56)))
#define MCUCR_REG		(*((volatile uint8_t*) (0x55)))
#define MCUCSR_REG		(*((volatile uint8_t*) (0x54)))
#define TCCR0_REG		(*((volatile uint8_t*) (0x53)))
#define TCNT0_REG		(*((volatile uint8_t*) (0x52)))
#define TCCR1A_REG		(*((volatile uint8_t*) (0x4F)))
#define TCCR1B_REG		(*((volatile uint8_t*) (0x4E)))
#define TCNT1H_REG		(*((volatile uint8_t*) (0x4D)))
#define TCNT1L_REG		(*((volatile uint8_t*) (0x4C)))
#define TCNT1_REG		(*((volatile uint16_t*)(0x4C)))
#define OCR1AH_REG		(*((volatile uint8_t*) (0x4B)))
#define OCR1AL_REG		(*((volatile uint8_t*) (0x4A)))
#define OCR1A_REG		(*((volatile uint16_t*)(0x4A)))
#define OCR1BH_REG		(*((volatile uint8_t*) (0x49)))
#define OCR1BL_REG		(*((volatile uint8_t*) (0x48)))
#define OCR1B_REG		(*((volatile uint16_t*)(0x48)))
#define ICR1H_REG		(*((volatile uint8_t*) (0x47)))
#define ICR1L_REG		(*((volatile uint8_t*) (0x46)))
#define TCCR2_REG		(*((volatile uint8_t*) (0x45)))
#define TCNT2_REG		(*((volatile uint8_t*) (0x44)))
#define OCR2_REG		(*((volatile uint8_t*) (0x43)))
#define ASSR_REG		(*((volatile uint8_t*) (0x42)))
#define WDTCR_REG		(*((volatile uint8_t*) (0x41)))
#define UBRRH_REG		(*((volatile uint8_t*) (0x40)))
#define UCSRC_REG		(*((volatile uint8_t*) (0x40)))
#define EEARH_REG		(*((volatile uint8_t*) (0x3F)))
#define EEARL_REG		(*((volatile uint8_t*) (0x3E)))
#define EEDR_REG		(*((volatile uint8_t*) (0x3D)))
#define EECR_REG		(*((volatile uint8_t*) (0x3C)))
#define SPDR_REG		(*((volatile uint8_t*) (0x2F)))
#define SPSR_REG		(*((volatile uint8_t*) (0x2E)))
#define SPCR_REG		(*((volatile uint8_t*) (0x2D)))
#define UDR_REG			(*((volatile uint8_t*) (0x2C)))
#define UCSRA_REG		(*((volatile uint8_t*) (0x2B)))
#define UCSRB_REG		(*((volatile uint8_t*) (0x2A)))
#define UBRRL_REG		(*((volatile uint8_t*) (0x29)))
#define ACSR_REG		(*((volatile uint8_t*) (0x28)))

#define TWDR_REG		(*((volatile uint8_t*) (0x23)))
#define TWAR_REG		(*((volatile uint8_t*) (0x22)))
#define TWSR_REG		(*((volatile uint8_t*) (0x21)))
#define TWBR_REG		(*((volatile uint8_t*) (0x20)))

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


#endif /* LIBRARY_REGISTER_H_ */
