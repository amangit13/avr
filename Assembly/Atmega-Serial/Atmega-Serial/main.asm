;
; Atmega-Serial.asm
;
; Created: 4/8/2021 10:31:44 PM
; Author : amana
;
.include "C:\Files\AVR\Assembly\common\mymacros_registers.inc"
.include "C:\Files\AVR\Assembly\common\mymacros.inc"

.dseg


.cseg
.org 0
	goto RESET


.org 0x0010
	.include "C:\Files\AVR\Assembly\common\atmegaserial.inc"
	goto RESET

RESET:
    serial_init_16M_9600
	serial_send_data 'A'
    goto RESET
