;
; Atmega-Serial.asm
;
; Created: 4/8/2021 10:31:44 PM
; Author : amana
;
#define _ATMEGA8_
.include "C:\Files\AVR\Assembly\common\mymacros_registers.inc"
.include "C:\Files\AVR\Assembly\common\mymacros_jump.inc"
.include "C:\Files\AVR\Assembly\common\mymacros_memory.inc"
.dseg

.cseg
.org 000 
	message1: .DB "HELLO WORLD. ",0
	goto RESET
.org 0x00C rcall serial_data_interrupt

.include "C:\Files\AVR\Assembly\common\myproc_utilities.inc"
.include "C:\Files\AVR\Assembly\common\myproc_atmega_serial.inc"


RESET:
	init_stack
    serial_init_16M_9600
	R20_ 0
	
	LOOP:
		serial_send_string_cseg message1
	
		inc R20
		R16__ R20
		serial_send_R16
		serial_send_data 32
		delay_1sec
	
    goto LOOP
