/*
 * Blink.c
 *
 * Created: 4/14/2020 8:59:25 PM
 * Author : aman
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0xff;
	PORTB = 0xff;
    /* Replace with your application code */
    while (1) 
    {
		_delay_ms(50);
		PORTB = 0x00;
		_delay_ms(50);
		PORTB = 0xff;
		
    }
}

