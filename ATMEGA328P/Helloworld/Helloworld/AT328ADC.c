//https://www.bing.com/?scope=web&mkt=en-US&FORM=INCOH1&pc=IC04
/*
ADMUX: REFS1 REFS0 ADLAR RESERVED MUX3 MUX2 MUX1 MUX0

ADCSRA: ADEN	ADSC	ADATE	ADIF	ADIE	ADPS2 ADPS1 ADPS0
		AD		start	auto	int		Int		pre scalar
		enable	 conv	trigger	flag	enable
			 

ADCSRB: NA, ACME, N, N,N, ADST2, ADST1, ADST0
							000 = free running
ADC: data register
*/
#ifndef _AT328_ADC_FREEFLOW 
#define _AT328_ADC_FREEFLOW 0
#endif 

void AT328_ADC_init()
{
	// Port C input
	DDRC = 0;
	
	// ADMUX 7,6 [voltage reference], ADLAR 5, MUX 4..0
	ADMUX = 0b01100000;
	
	ADCSRA = 0b10000111 | _AT328_ADC_FREEFLOW <<ADATE | _AT328_ADC_FREEFLOW << ADIE;
}


int_fast8_t AT328_ADC_read()
{
	ADCSRA |= 0b01000000;
	
	while(ADCSRA & 0b01000000);
	
	return ADCH;
}

// define _ADC_EXTERN_VECT to use your own external isr
#ifndef _AT328_ADC_EXTERN_VECT
ISR(ADC_vect)
{

}
#endif
