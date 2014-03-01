/*
 * Nanite.h
 *
 * Created: 27.10.2013 13:43:26
 *  Author: tim , cpldcpu@gmail.com
 */ 


#ifndef NANITE_H_
#define NANITE_H_

#include <util/delay.h>
#include <avr/wdt.h>
#include <avr/io.h>
#include <stdio.h>

/*
	This is usually PB5
*/

#define NANITE_PORT PORTB
#define NANITE_DDR  DDRB
#define NANITE_INP  PINB
#define NANITE_PIN  PB5

/*
*	serial output
*/

#define NANITE_BAUD 9600

void nanite_sendbyte(char);
extern int nanite_putchar(char c, FILE *stream);
 
#define nanite_init_stdout() { \
	static FILE nanite_stdout = FDEV_SETUP_STREAM(nanite_putchar, NULL, _FDEV_SETUP_WRITE); \
	stdout = &nanite_stdout; \
}

/*
	nanite_init
	
	input:  none
	output: none
	
	Initialize pin and turn LED off
*/

#define nanite_init() { \
	NANITE_PORT &=~_BV(NANITE_PIN); \
	NANITE_DDR &=~_BV(NANITE_PIN); \
}

/*
	nanite_poll

	input:  none
	output: none

	nanite_poll_led
	
	input:  boolean to turn the LED on or off
	output: none

	Reads the state of the reset switch. Uses the watch dog timer to issue a reset when the button is pressed.		
*/

#define nanite_poll_led(ledon) { \
	NANITE_DDR &=~_BV(NANITE_PIN); \
	_delay_us(5); \
	if (!(NANITE_INP & _BV(NANITE_PIN))) wdt_enable(WDTO_15MS); \
	if (ledon) NANITE_DDR |=_BV(NANITE_PIN); \
}

#define nanite_poll() { \
	uint8_t nanite_tmp=NANITE_DDR;\
	NANITE_DDR &=~_BV(NANITE_PIN); \
	_delay_us(5); \
	if (!(NANITE_INP & _BV(NANITE_PIN))) wdt_enable(WDTO_15MS); \
	NANITE_DDR =nanite_tmp; \
}


/*
	nanite_led
	
	input:  boolean to turn the LED on or off
	output: none

	Turns LED on or off without polling the reset switch. Use this if you do not want the reset functionality.
*/

#define nanite_setled(ledon) { \
	NANITE_DDR &=~_BV(NANITE_PIN); \
	if (ledon) NANITE_DDR |=_BV(NANITE_PIN); \
}

#define nanite_init_wdt() { \
	wdt_enable(WDTO_500MS); \
	NANITE_PORT &=~_BV(NANITE_PIN); \
	NANITE_DDR &=~_BV(NANITE_PIN); \
}

#define nanite_poll_wdt(a) { \
	NANITE_DDR &=~_BV(NANITE_PIN); \
	_delay_us(5); \
	if (NANITE_INP & _BV(NANITE_PIN)) wdt_reset(); \
	if (a) NANITE_DDR |=_BV(NANITE_PIN); \
}


#endif /* NANITE_H_ */