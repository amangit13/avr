;
; AtmegaTimer.asm
;
; Created: 5/28/2021 3:05:25 AM
; Author : amana
;
.include "mymacros_registers.inc"
.include "mymacros_jump.inc"
.include "mymacros_memory.inc"

; Replace with your application code
start:
	memory.init_m_stack()
	rcall setup_timer1_toggleA

	loop:
    goto loop

	/*
		able to set frequency
		able to change frequency
		able to react to time events
		able to toggle pin
		set above for all timers
		intuitive to use
			timer1.setMode(TogglePinA, frequency)
			timer1.setMode(CallInterrupt, frequency, handler)
	*/
	setup_timer1_toggleA:
		r16_ 0xff
		out DDRB, r16 ; // pin 15 is output pin for OC1A
						// pin 16 is output pin for OC1B

		
		// set OCR1A value to 0 to compare
		r16_ 0x0
		sts OCR1AH, r16
		r16_ 0x0
		sts OCR1AL, r16

		// set OCR1B value to x to compare. 
		r16_ 0x0
		sts OCR1BH, r16
		r16_ 0x1
		sts OCR1BL, R16

		r16_ 1<<COM1B0
		sts TCCR1A, r16 // toggle oc1a & oc1b on compare
	
		//	       ctc  prescalar
		r16_ 0b00001001
		sts TCCR1B, r16 // set prescalar to 1 and set CTC mode
	return
