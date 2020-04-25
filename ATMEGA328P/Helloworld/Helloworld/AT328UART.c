#include <avr/interrupt.h>
// http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf
// page 165. 
#define BAUD 1000000
#define MYUBRR (((F_CPU / (BAUD * 16UL))) - 1)volatile char *AT328UART_buffer;

// pg 149
void AT328_UART_init()
{
/*Set baud rate */
UBRR0H = (unsigned char)(MYUBRR>>8);
UBRR0L = (unsigned char)MYUBRR;
UCSR0B |= (1<<TXEN0) | (1<<TXCIE0);

/* Set frame format: 8data, 2stop bit */
UCSR0C = 0b00000110;
sei();

}
	
// pg 150
void AT328_UART_out(int_fast8_t data)
{
	/* Wait for empty transmit buffer */
	/* Put data into buffer, sends the data */
	UDR0 = data;}

void AT328_UART_outs(char * data)
{
	AT328UART_buffer = data; 
	UDR0 = *AT328UART_buffer++;
}

unsigned char AT328_UART_in(void)
{
	/* Wait for data to be received */
	while (!(UCSR0A & (1<<RXC0)));
	/* Get and return received data from buffer */
	return UDR0;
}

// define _AT328UART_EXTERN_VECT to use external isr
#ifndef _AT328_UART_EXTERN_VECT
ISR(USART_TX_vect)
{
	if (*AT328UART_buffer)
		UDR0 = *AT328UART_buffer++;
}
#endif
