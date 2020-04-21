/*
 *
 * Created: 10/3/2018 10:32:55 AM
 * Author : home
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "AT328UART.c"
#include "Blink.c"

int main(void)
{
	USART_Init();
	_delay_ms(1000);
	
	while (1)
	{
		USART_Transmit(0xFF);
	}
}

