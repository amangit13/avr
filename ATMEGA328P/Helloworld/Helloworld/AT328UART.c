#include <avr/interrupt.h>
// http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf
// page 165. 
#define BAUD 250000
#define MYUBRR (((F_CPU / (BAUD * 16UL))) - 1)
// pg 149
void USART_Init()
{
/*Set baud rate */
UBRR0H = (unsigned char)(MYUBRR>>8);
UBRR0L = (unsigned char)MYUBRR;
UCSR0B = (1<<TXEN0);
/* Set frame format: 8data, 2stop bit */
UCSR0C = 0b00000110;
}
	
// pg 150
void USART_Transmit(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1<<UDRE0)));
	/* Put data into buffer, sends the data */
	UDR0 = data;	//UCSR0B |= 1<<UDRIE0;}

unsigned char USART_Receive(void)
{
	/* Wait for data to be received */
	while (!(UCSR0A & (1<<RXC0)))
	;
	/* Get and return received data from buffer */
	return UDR0;
}

 