.set CPUF=8000000
.include "mymacros_registers.inc"
.include "mymacros_jump.inc"
.include "mymacros_memory.inc"
.include "mymacros_io.inc"
.include "mymacros_math.inc"

.org 000 goto MAIN
.include "myproc_utils.asm"
.include "myproc_atmega_serial.asm"


MAIN:
	init_m8_stack
	serial.init_8M_9600
	io.PB.setPinMode 0, IO_OUTPUT
	R19_ 10

	MAIN_REPEAT:
		serial.sendRegByte R19
		io.PB.togglePin 0
		util.delay_10msec

		dec R19
		if_zero_goto MAIN_REPEAT2

	goto MAIN_REPEAT

	MAIN_REPEAT2:
		io.PB.togglePin 0
		util.delay_1sec
	goto MAIN_REPEAT2
	
