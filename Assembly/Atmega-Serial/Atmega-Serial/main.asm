;
; Atmega-Serial.asm
;
; Created: 4/8/2021 10:31:44 PM
; Author : amana
;

#define _8MHZ_
.include "mymacros_registers.inc"
.include "mymacros_jump.inc"
.include "mymacros_memory.inc"
.include "mymacros_math.inc"
.include "mymacros_io.inc"
.dseg

.cseg
.org 000 goto MAIN
.org 0x00C rcall serial_data_interrupt


.include "myproc_utils.asm"
.include "myproc_atmega_serial.asm"
.include "myproc_string.asm"

MAIN:
	init_m8_stack
    serial.init_8M_9600
	R20_ 200
	io.PB.setPinMode IO_OUTPUT, 0

	message1: .DB "HELLO WORLD. value = ",0

	LOOP:
		io.PB.togglePin 0
		inc R20
		serial.send_string_cseg message1
		
		R18__ R20
		string.hexToStr_R18R19
		serial.sendRegByte R18
		serial.sendRegByte R19

		serial.sendByte serial.LINE_FEED

		util.delay_100msec
    goto LOOP

