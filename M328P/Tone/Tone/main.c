/*
 * Tone.c
 *
 * Created: 10/3/2018 10:38:50 AM
 * Author : home
 */ 
#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "ToneGenerator.c"


int main(void)
{
	
	setupToneGenerator();
	setNote(C4);
	setInstrument(instrumentNoise);
		
	while(1)
	{
		stopSound();
		_delay_ms(90);
		startSound();
		_delay_ms(10);
	}	
}

