;
; blink.asm
;
; Created: 3/28/2021 8:55:21 AM
; Author : amana
;
.include "mymacros.inc"

R16_ 255
SET_PB_OUT 1

for:
dec r16
not_zero_goto (for)

R16_ 255

loop_infinity:

	loopA:
		R17_ 255

		loopB:
		dec_while_r17_not_0 (loopB)

	dec_while_R16_not_0 (loopA)

	TOGGLE_PB (0)

goto loop_infinity
