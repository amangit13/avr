#include<avr/interrupt.h>

// must declare the timer interrupt routine in the main program
// ISR(TIMER1_OVF_vect)
void setupTimer()
{

    TCCR1B = 2; // set prescalar to 8. 16MHz / 8 / 65K overflow = 30.769Hz
    
    // initialize counter
    TCNT1 = 0;
    
    // enable overflow interrupt
    TIMSK1 |= (1 << TOIE1);
    
    // enable global interrupts
    sei();
}

void disableTimer()
{
	TIMSK1 &= ~(1 << TOIE1);
}

/*

SetupTimerOverFlowInterrupt (timer number)

SetupTimerCompareInterrupt (timer number, compare int)








*/