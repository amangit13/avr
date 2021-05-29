.set CPUF=20000000

.include "mymacros_registers.inc"
.include "mymacros_jump.inc"
.include "mymacros_memory.inc"
.include "mymacros_io.inc"
;.include "mymacros_math.inc"

.org 000 goto MAIN
;.include "myproc_atmega_timer.asm"
;.include "myproc_utils.asm"
;.include "myproc_atmega_serial.asm"


MAIN:
	init_m8_stack
	io.PB.setPinMode 0, IO_OUTPUT

	MAIN_REPEAT:
		io.PB.togglePin 0
	goto MAIN_REPEAT
