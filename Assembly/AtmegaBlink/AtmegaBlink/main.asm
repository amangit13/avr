#define _8MHZ_
.include "mymacros_registers.inc"
.include "mymacros_jump.inc"
.include "mymacros_memory.inc"
.include "mymacros_io.inc"
.include "mymacros_math.inc"

.dseg


.cseg
.org 000 goto RESET
.include "myproc_utils.asm"

RESET:

	init_m8_stack
	io.PB.setPinMode 1, IO_OUTPUT
	io.PB.PinOn 1
	io.PB.setPinMode 0, IO_OUTPUT
	io.PB.PinOff 0

	MAIN_REPEAT:
		io.PB.togglePin 1
		io.PB.togglePin 0
		util.delay_100msec
		goto MAIN_REPEAT

