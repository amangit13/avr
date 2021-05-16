#ifndef _9_6MHZ_
	#ifndef _8MHZ_
		#ifndef _16MHZ_00
			#ifndef _20MHZ_
				.error "Make sure to define _9_6MHZ_ or _8MHZ_ or _16MHZ_ or _20MHZ_ TO USE DELAY METHOD"
			#endif
		#endif
	#endif
#endif

;.set _v1 = 50000
;.set _v2 = 40

.macro util.delay_100msec
	.set _v1 = 20000
	.set _v2 = 10
	rcall _delayw_loops
.endm

.macro util.delay_1sec
	.set _v1 = 1000
	.set _v2 = 4
	rcall _delayw_loops
.endm

_delayw_loops:

	push3 R18,R24,R25

	R18_ _v2

	_dlyw_start:
		R24_ low(_v1)
		R25_ high(_v1)

	_dlyw_loop:
		subtract_int R24, 1					; 2 cycle
		if_not_zero_goto _dlyw_loop			; 2 cycle for jmp, 1 for else. 

		dec R18								; 1 cycle
		if_not_zero_goto _dlyw_start			; 2 cycle

	pop3 R18,R24,R25
ret