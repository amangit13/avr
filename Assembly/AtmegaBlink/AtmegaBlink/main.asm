#define _8MHZ_
.include "mymacros_registers.inc"
.include "mymacros_jump.inc"
.include "mymacros_memory.inc"
.dseg


.cseg
.org 000 rjmp RESET
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

init_m8_stack
set_PB_out 0
PB_on 0

REPEAT:
delay_10ms

toggle_PB 0

goto REPEAT
