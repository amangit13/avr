//https://www.bing.com/?scope=web&mkt=en-US&FORM=INCOH1&pc=IC04
void ADC_init()
{
	// Port C input
	DDRC = 0;
	
	// ADMUX 7,6 [voltag reference], ADLAR 5, MUX 4..0
	ADMUX = 0b01100000;
	
	ADCSRA = 0b10000111;
}


int_fast8_t ADC_read()
{
	ADCSRA |= 0b01000000;
	
	while(ADCSRA & 0b01000000);
	
	return ADCH;
}

