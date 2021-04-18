;
; Atmega-Serial.asm
;
; Created: 4/8/2021 10:31:44 PM
; Author : amana
;
#define _ATMEGA8_
.include "mymacros_registers.inc"
.include "mymacros_jump.inc"
.include "mymacros_memory.inc"
.dseg


.cseg
.org 000 
	goto RESET
.org 0x00C rcall serial_data_interrupt

.include "myproc_utilities.inc"
.include "myproc_atmega_serial.inc"

message1: .DB "HELLO WORLD. ",0

RESET:
	init_stack
    serial_init_16M_9600
	R20_ 200
	R21_ 1 ; positive direction

	LOOP:
		;serial_send_string_cseg message1
		
		; --------------------- Set direction ----------------------
		if_reg_equ_goto R20,1,positive
			else0: 
				if_reg_equ_goto R20,255,negative
			else1: 
				goto cont

		positive:
			R21_ 1
			goto cont
		negative:
			R21_ 0
			goto cont
		;------------------------------------------------------------


		;------------------ check direction and send data ----------
		cont:

		if_reg_equ_goto R21,1,increase
		else00: dec R20
			goto send_data
		increase:
			inc R20
		
		send_Data: serial_send_reg_data R20
		delay_1sec
    goto LOOP

