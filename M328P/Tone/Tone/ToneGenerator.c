#define C3 7645
#define D3 6810
#define E3 6067
#define F3 5405
#define G3 4816
#define A4 4290
#define B4 3822
#define C4 3405

volatile int _tonegeneratorOC1A = B4;

// setup CTC mode to generate tone. Must also call playSound to start the tone.
void setupToneGenerator()
{
	
	// setup port direction so that OC1A i.e., port PB1 can be toggled.
	DDRB |= 1<<PORTB1;
	
	// toggle OC1A pin on compare match. non pwm
	TCCR1A |= (1 <<COM1A0);
	
	// CTC mode clear timer on compare match. mode 4
	// TCCR1A bit 0 & 1 are zero & TCCR1B bit 3 is 1.
	TCCR1B |= (1<<WGM12);
	
	// set compare value
	TCNT1 = 0;

	OCR1A = _tonegeneratorOC1A;

	// setup interrupt on compare match OCR1A
	TIMSK1 |= 1<< OCIE1A;
	
	sei();
	
	// Select clock source and prescalaing. this will start the timer.
	//TCCR1B |= (1<< CS11);
}

inline void setNote(uint16_t note)
{
	_tonegeneratorOC1A = note;
}

inline void setFreq(uint16_t freq)
{
	_tonegeneratorOC1A = 1000000/freq;	
}

inline void stopSound()
{
	TCCR1B &= ~(1<< CS11);
	TCNT1 = 0;
}

// must call each time stop is called otherwise tone will not generate.
inline void startSound()
{

	TCCR1B |= (1<<CS11);
}

ISR(TIMER1_COMPA_vect)
{
	// change OCRA to a new frequency. It is done in the interrupt to avoid comparing compa with a non zero timer counter.
	OCR1A = _tonegeneratorOC1A;
	
}
