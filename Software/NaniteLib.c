/*
 * NaniteLib.c
 *
 * Created: 09.11.2013 07:15:26
 *  Author: tim
 */ 

#include "Nanite.h"

int nanite_putchar(char c, FILE *stream)
{
	if (c == '\n') nanite_sendbyte('\r');
	nanite_sendbyte(c);
	
	return 0;
}


void nanite_sendbyte(char data)
{
	uint8_t i;
	
	NANITE_DDR |=_BV(NANITE_PIN);  // 0
	_delay_us(1000000/NANITE_BAUD);
	
	for (i=0; i<8; i++)
	{
		if (data&1)
		NANITE_DDR &=~_BV(NANITE_PIN); // 1
		else
		NANITE_DDR |=_BV(NANITE_PIN);  // 0
		data>>=1;
		_delay_us(1000000/NANITE_BAUD);
	}

	NANITE_DDR &=~_BV(NANITE_PIN); // 1
	_delay_us(1000000/NANITE_BAUD);
}
