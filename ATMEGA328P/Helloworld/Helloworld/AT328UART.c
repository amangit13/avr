#include <avr/interrupt.h>
// http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf
// page 165. 
#define BAUD 500000
#define MYUBRR (((F_CPU / (BAUD * 16UL))) - 1)volatile char *buffer;

// pg 149
void USART_Init()
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
void serialout(int_fast8_t data)
{
	/* Wait for empty transmit buffer */
	/* Put data into buffer, sends the data */
	UDR0 = data;}

void serialouts(char * data)
{
	buffer = data; 
	UDR0 = *buffer++;
}

unsigned char serialin(void)
{
	/* Wait for data to be received */
	while (!(UCSR0A & (1<<RXC0)));
	/* Get and return received data from buffer */
	return UDR0;
}

ISR(USART_TX_vect)
{
	if (*buffer)
		UDR0 = *buffer++;
}