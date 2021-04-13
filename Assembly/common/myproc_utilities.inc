;---------------------------------- DLY ------------------------------------------
#ifdef _ATTINY13_						; must #define _ATTINY13A_ to use this function
_attiny13_delay_1sec:
	R18_ 0
	R16_ 255
	R17_ 255

	attiny13_r18:
	
		attiny13_r16:
			
			attiny13_r17: 
			repeat_until_r17_0 attiny13_r17
		
		repeat_until_r16_0 attiny13_r16
	
	repeat_until R18,48, attiny13_r18
RET
#endif

#ifdef _ATMEGA8_						; must #define _ATMEGA8_ to use this function
_atmega8_delay_1sec:
	R18_ 0
	R16_ 255
	R17_ 255

	atmeg8_r18:
	
		atmeg8_r16:
	
			atmeg8_r17: 
			repeat_until_r17_0 atmeg8_r17
		
		repeat_until_r16_0 atmeg8_r16
	
	repeat_until R18,48,atmeg8_r18
RET
#endif

.macro delay_1sec
	#ifdef _ATMEGA8_
		rcall _atmega8_delay_1sec
	#endif
		
	#ifdef _ATTINY13_
		rcall _attiny13_delay_1sec
	#endif
.endm

;---------------------------------STANDARD BLINK TEST PORTB 0-----------------
.macro blink_test
	set_PB_out 0
	_blink_test_loop:	
		delay_1sec
		toggle_PB (0)
	rjmp _blink_test_loop
.endm
