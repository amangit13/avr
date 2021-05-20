// generate clock frequency of 1 Khz using timer and read input at ADC0 pin #28
// TCCR1A: COM1A, COM1A, COM1B, COM1B,  --, --, WGM11, WGM10
// TTCR1B ICN1, ICES1, --, WGM13, WGM12, CS12, CS11, CS10
//											0	0	1 = Prescalaing 001 - 101, clk/1 - cls/1024 (1, 8, 64, 256, 1024)
// TCCR1C 
//
void AT328_Logic_init(uint_fast16_t delay)
{
	
	// setup port direction so that OC1A i.e., port PB1 can be toggled. pin #15
	DDRB |= 1<<PORTB1;
	
	// toggle OC1A pin on compare match. non pwm
	TCCR1A |= (1 <<COM1A0);
	
	// CTC mode clear timer on compare match. mode 4
	// TCCR1A bit 0 & 1 are zero & TCCR1B bit 3 is 1.
	TCCR1B |= (1<<WGM12);
	
	// set compare value
	TCNT1 = 0;
	OCR1A = delay;

	// setup interrupt on compare match OCR1A
	TIMSK1 |= 1<< OCIE1A;
	
	sei();
	
	// Select clock source and prescalaing. this will start the timer. prescalar = 256
	TCCR1B |= (1<< CS12); 
}

ISR(TIMER1_COMPA_vect)
{
	//TCNT1 = 0;
	// measure input
}