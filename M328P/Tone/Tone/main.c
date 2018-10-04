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
	setNote(A4);
	setTone(toneSquareWave);
	
	int i = 0;
	
	while(1)
	{
		i = 0;
		setNote(C4);
		
		while(i < 50)
		{
			i++;
			stopSound();
			_delay_ms(100);
			startSound();
			_delay_ms(10);
		}
	
		stopSound();
		for (i = 100; i<2000; i+=20)
		{
			_delay_ms(100);
			setFreq (i);
			startSound();
			_delay_ms(10);
			stopSound();
		}
	}
	
	
}

