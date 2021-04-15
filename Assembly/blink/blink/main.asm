;
; blink.asm
;
; Created: 3/28/2021 8:55:21 AM
; Author : amana
;
.device attiny13a

.include "C:\Files\AVR\Assembly\common\mymacros.inc" ; import macros

;----------------------------------- DATA SEG global variables ------------------------------------
.DSEG
	VAR1: .byte 1
	.macro VAR1_;(register)
		set_var VAR1,@0
	.endm
	.macro _VAR1;(register)
		read_var @0,VAR1
	.endm

;----------------------------------- CODE SEG. main program --------------------------------------
.CSEG
.ORG 0x0
	goto REST

.ORG 0x0010
	.include "C:\Files\AVR\Assembly\common\myutilities.inc" ; import utilities such as delay functions

REST:
	set_PB_out (0)
	R21_ 128

	loop_infinity:	
		RCALL delay_1_sec
		toggle_PB (0)

	inc R21
	VAR1_ R21

	goto loop_infinity
