
.macro delay_1sec
.message "!!!!!!!!!!!!!!!!!!DEFINE _attiny13 or _atmega8 TO USE DELAY METHOD !!!!!!!!!!!!!!!!!!!!!!"

	#ifdef _attiny13_
		rcall delay_1sec_attiny13_9_6mhz
	#endif
.endm

#ifdef _attiny13_

delay_1sec_attiny13_9_6mhz:
	.equ _v1 = 232
	.equ _v2 = 249
	.equ _v3 = 55

	R16_ _v1
	R17_ _v2
	R18_ _v3

	_dly_loop:
		dec R16							; 1 cycle			
		if_not_zero_goto _dly_loop		; 2 for jmp
		R16_ _v1						; 2. 1+1 cycle.  1 for no jump and 1 for reg assingment

		dec R17							; 1 cycle
		if_not_zero_goto _dly_loop		; 2	for jmp
		R17_ _v2						; 2. 1+1 cycle. same as above

		dec R18							; 1
		if_not_zero_goto _dly_loop
ret
#endif
