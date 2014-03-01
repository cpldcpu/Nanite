/*
 * NaniteExamples.c
 *
 * Created: 27.10.2013 13:43:04
 *  Author: tim
 */ 


#include "Nanite.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>


int main(void)
{
	uint8_t blink=0;
	
	nanite_init();		// Initialize nanite pin
	nanite_init_stdout();

    while(1)
    {
	
		printf("test %i\n",blink);
	
		nanite_poll();		// poll reset button and update LED
		
		blink^=1;
		_delay_ms(500);
        //TODO:: Please write your application code 
    }
}