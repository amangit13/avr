// uses OCR1A i.e, PCB1 pin to generate tones. Connect speaker to PB1 with a 220 resistor.

#define C3 7645
#define D3 6810
#define E3 6067
#define F3 5405
#define G3 4816
#define A4 4290
#define B4 3822
#define C4 3405

#define toneNoise 1
#define toneSquareWave 0

volatile int _tonegenOC1A = B4;

volatile uint8_t _toneName = toneSquareWave;

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

	OCR1A = _tonegenOC1A;

	// setup interrupt on compare match OCR1A
	TIMSK1 |= 1<< OCIE1A;
	
	sei();
	
	// Select clock source and prescalaing. this will start the timer.
	//TCCR1B |= (1<< CS11);
}
inline void setTone(uint8_t toneName)
{
	_toneName = toneName;
}
inline void setNote(uint16_t note)
{
	_tonegenOC1A = note;
}

inline void setFreq(uint16_t freq)
{
	_tonegenOC1A = 1000000/freq;	
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
	switch(_toneName)
	{
		case toneNoise:
		OCR1A = rand()%1000 + 100;
		TCNT1 = 0;
		break;
		
	// change OCRA to a new frequency. It is done in the interrupt to avoid comparing compa with a non zero timer counter.
		default:
		OCR1A = _tonegenOC1A;
		TCNT1 = 0;
	}
	
}
