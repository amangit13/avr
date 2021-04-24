#ifndef _9_6MHZ_
	#ifndef _8MHZ_
		#ifndef _16MHZ_00
			#ifndef _20MHZ_
				.error "Make sure to define _9_6MHZ_ or _8MHZ_ or _16MHZ_ or _20MHZ_ TO USE DELAY METHOD"
			#endif
		#endif
	#endif
#endif



.macro delay_1sec
	.set _v1H = 0xC3 ; C350 = 50,000
	.set _v1L = 0x50 ; 50,000
	.set _v2 = 40
	rcall _delayw_loops
.endm

.macro delay_1ms
	.set _v1H = 0x02
	.set _v1L = 0x9A
	.set _v2 = 3
	rcall _delayw_loops
.endm

.macro delay_10ms
	.set _v1H = 0x1A
	.set _v1L = 0x0A
	.set _v2 = 3
	rcall _delayw_loops
.endm



_delayw_loops:

	R18_ _v2

	_dlyw_start:
		LDI R24, _v1L
		LDI R25, _v1H

	_dlyw_loop:
		SBIW R25:R24, 1					; 2 cycle
	if_not_zero_goto _dlyw_loop			; 2 cycle for jmp, 1 for else. 
										; add nop to make else 2 cycle as well
										; 1 cycle to make this loop 4 cycle as well
		dec R18							; 1 cycle
	if_not_zero_goto _dlyw_start			; 2 cycle
ret