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
	setNote(C3);
	startSound();
	
	_delay_ms(1000);
	
	uint16_t freq = 100;
	int8_t step = 30;
    /* Replace with your application code */
    while (1)
    {
		freq += step;
		setFreq(freq);
		_delay_ms(30);
		if (freq >= 2000 || freq <= 100)
		{
			step *= -1;
			freq += step;
			stopSound();
			_delay_ms(400);
			startSound();		
		}

    }
}

