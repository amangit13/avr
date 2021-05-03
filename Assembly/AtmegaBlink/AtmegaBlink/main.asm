#define _8MHZ_
.include "mymacros_registers.inc"
.include "mymacros_jump.inc"
.include "mymacros_memory.inc"
.include "mymacros_io.inc"
.dseg


.cseg
.org 000 goto RESET
.org 0x12 RETI
.org 0x008 goto _timer_interrupt

.org 0x13
.include "myproc_math.inc"
.include "myproc_atmega_serial.inc"
;.include "myproc_utilities.inc"
.include "myproc_atmega_timer.inc"

RESET:

init_m8_stack
io.PB.setPinMode 0, IO_OUTPUT
io.PB.PinOn 0
serial.init_8M_9600

timer1.begininterrupt	
sei

MAIN_REPEAT:
	goto MAIN_REPEAT


_timer_interrupt:
	io.PB.togglePin 0
reti