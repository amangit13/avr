#include <avr/interrupt.h>
void setupCTC()
{
		TCCR0A = 0;		// normal mode
		TCCR0B = 5;		// prescala selected as 5 = 1024
		TIMSK0 = 2;		// enable timer overflow interrupt
		sei();			// enable interrupt
}

ISR(TIM0_COMPA_vect)
{
	
}

ISR(TIM0_OVF_vect)
{
}