#define _atmega8_
.include "mymacros_registers.inc"
.include "mymacros_jump.inc"
.include "mymacros_memory.inc"
.dseg


.cseg
.org 000 goto RESET
RETI ; interrupt vectors
RETI
RETI
RETI
RETI
RETI
RETI
RETI
RETI
RETI
RETI
RETI
RETI
RETI
RETI
RETI
RETI
RETI

.include "myproc_utilities.inc"
;.include "myproc_atmega_serial.inc"
goto RESET


RESET:

init_stack
set_PB_out 0

REPEAT:
toggle_PB 0
delay_1sec

goto REPEAT
