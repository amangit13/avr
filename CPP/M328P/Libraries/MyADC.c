#include <avr/interrupt.h>
uint16_t _ADCW;

// enableInt= 1 to setup interrupt
void setupADC(uint8_t enableInt)
{
	ADMUX = 0b01000000; // REFS to 01 for AVCC. ADLAR to 1 for righ adjust results. MUX to 0 for ADC0 port as input.
	
	if (enableInt)
	{	
		ADCSRA = 0b11001011; // start the conversion. with interrupt
		sei();
	}
	
	
	DIDR0 = 0; // disable digital input to all ADC ports.
}

// call this method to read ADC if interrupt is not set. otherwise, read _ADCW variable directly that is set via interrupt. 
uint16_t readADC()
{
		ADCSRA = 0b11000111; // start the conversion. with prescalar to 128
		
		while (ADCSRA & 0b01000000);
		
		return ADCW;

}

ISR(ADC_vect)
{
	// read latest value
	_ADCW = ADCW;
	ADCSRA =  0b11001011; // start the conversion. with interrupt
	sei();
	//reti();
}