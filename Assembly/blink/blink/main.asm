;
; blink.asm
;
; Created: 3/28/2021 8:55:21 AM
; Author : amana
;
.device attiny13a

.include "mymacros.inc"

.DSEG
	VAR1: .byte 1
	.macro VAR1_;(register)
		set_var VAR1,@0
	.endm
	.macro _VAR1;(register)
		read_var @0,VAR1
	.endm
	.macro VAR1_add;(val)
		push R16
		_VAR1 R16
		ADDI R16,@0
		VAR1_ R16
		POP R16	
	.endm
.CSEG
.ORG 0x0
goto REST

.ORG 0x0010
.include "myutilities.inc"


REST:
R21_ 128
set_PB_out (0)

loop_infinity:	
	RCALL delay_1_sec
	toggle_PB (0)

inc R21
VAR1_ R21

goto loop_infinity

