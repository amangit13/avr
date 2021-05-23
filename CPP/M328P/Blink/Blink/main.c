/*
 * Blink.c
 *
 * Created: 10/3/2018 10:32:55 AM
 * Author : home
 */ 

#define F_CPU 20000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0xff;
	
    /* Replace with your application code */
    while (1) 
    {
		PORTB = 0xff;
		_delay_ms(500);
		PORTB = 0;
		_delay_ms(500);
    }
}

