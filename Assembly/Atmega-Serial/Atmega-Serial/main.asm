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
.org 0x0000
	goto RESET


.include "C:\Files\AVR\Assembly\common\myproc_utilities.inc"
.include "C:\Files\AVR\Assembly\common\myproc_atmega_serial.inc"
goto RESET

message: .DB "HELLO WORLD",0

RESET:
	init_stack
    serial_init_16M_9600

setpointer: PointAtProgConst message
	
	LOOP:
		LoadValueOfProgConst_R0
		
		if_register_equal_skip_next R0,0 
			goto continue
		delay_1sec
		goto setpointer
	
		continue:
			serial_send_data R0
			inc ZL
	
    goto LOOP


;--------------- constants --------------

