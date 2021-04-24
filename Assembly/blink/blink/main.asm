;
; blink.asm
;
; Created: 3/28/2021 8:55:21 AM
; Author : amana
;
#define _atmega8_

.include "mymacros_jump.inc" ; import macros
.include "mymacros_registers.inc" ; import macros
.include "mymacros_memory.inc"

;----------------------------------- CODE SEG. main program --------------------------------------
.CSEG
.ORG 0x0
	goto RESET

	.include "myproc_utilities.inc" ; import utilities such as delay functions

RESET:
	init_stack
	set_PB_out (0)
	PB_off 0

	repeat:
		toggle_PB 0
		delay_1sec
	goto repeat
goto RESET
