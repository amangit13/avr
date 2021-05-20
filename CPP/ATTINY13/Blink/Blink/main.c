/*
 * Blink.c
 *
 * Created: 4/14/2020 8:59:25 PM
 * Author : aman
 */ 

#include <avr/io.h>
#include <util/delay_basic.h>
#include <util/delay.h>
#include "Timmer.c"
#include "UART.c"


#define _NOP __asm__ __volatile__ ("nop");


int main(void)
{
	DDRB = 0xff;
	PORTB = 0xff;
	
	//setupCTC();
	while (1)
	{
		sbyte(65);
	}
}