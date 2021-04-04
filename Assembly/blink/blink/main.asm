;
; blink.asm
;
; Created: 3/28/2021 8:55:21 AM
; Author : amana
;
.include "mymacros.inc"

.ORG 0x0
goto REST

.ORG 0x0010
.include "myutilities.inc"

REST:
SET_PB_OUT (0)

loop_infinity:	
	RCALL delay_1_sec
	RCALL delay_1_sec
	TOGGLE_PB 0
goto loop_infinity

