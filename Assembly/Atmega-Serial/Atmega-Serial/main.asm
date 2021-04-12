;
; Atmega-Serial.asm
;
; Created: 4/8/2021 10:31:44 PM
; Author : amana
;
#define _ATMEGA8_
.include "C:\Files\AVR\Assembly\common\mymacros_registers.inc"
.include "C:\Files\AVR\Assembly\common\mymacros.inc"

.dseg


.cseg
.org 0x0000
	goto RESET
	reti
	reti

.include "C:\Files\AVR\Assembly\common\myutilities.inc"
.include "C:\Files\AVR\Assembly\common\atmegaserial.inc"
goto RESET

RESET:
	init_stack

    serial_init_16M_9600
	LOOP:
	serial_send_data 65
	delay_1sec
    goto LOOP
