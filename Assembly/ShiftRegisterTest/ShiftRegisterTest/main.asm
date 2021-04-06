;
; ShiftRegisterTest.asm
;
; Created: 4/4/2021 4:44:37 PM
; Author : amana
;
.include "C:\Files\AVR\Assembly\common\mymacros.inc"
.include "C:\Files\AVR\Assembly\common\mymacros_registers.inc"
.cseg
	; variables

.org 0x0000
goto RESET
.include "C:\Files\AVR\Assembly\common\myutilities.inc"

RESET:
