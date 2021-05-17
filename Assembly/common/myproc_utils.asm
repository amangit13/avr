/*#ifndef _9_6MHZ_
	#ifndef _8MHZ_
		#ifndef _16MHZ_00
			#ifndef _20MHZ_
				.error "Make sure to define _9_6MHZ_ or _8MHZ_ or _16MHZ_ or _20MHZ_ TO USE DELAY METHOD"
			#endif
		#endif
	#endif
#endif*/

.macro util.delay_1msec;
	push r19

	R24_ low(666)	; loop1 = 666
	R25_ high(666)
	R19_ 3			; loop2 = 3
	
	rcall _delayw_loops
	pop r19
.endm

.macro util.delay_10msec
	push r19

	R24_ low(20000)	; loop1 = 20000
	R25_ high(20000)
	R19_ 10			; loop2 = 10
	
	rcall _delayw_loops
	pop r19

.endm

.macro util.delay_100msec
	push r19

	R24_ low(19999)
	R25_ high(19999)
	R19_ 10

	rcall _delayw_loops
	pop r19
.endm


.macro util.delay_1sec
	push R19

	R24_ low(50000)
	R25_ high(50000)
	R19_ 40

	rcall _delayw_loops
	pop r19
.endm

_delayw_loops:

	push2 R24,R25 ; save to stack so that these can be pop

	_dlyw_start:
		pop2 R25, R24	; get original values
		push2 R24, R25	; save original values

	_dlyw_loop:
		subtract_int R24, 1					; 2 cycle
		if_not_zero_goto _dlyw_loop			; 2 cycle for jmp, 1 for else. 

		dec R19								; 1 cycle
		if_not_zero_goto _dlyw_start			; 2 cycle

	pop2 R25,R24 ; empty the stack
ret
