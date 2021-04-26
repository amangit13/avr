#define _8MHZ_
.include "mymacros_registers.inc"
.include "mymacros_jump.inc"
.include "mymacros_memory.inc"
.dseg


.cseg
.org 000 NOP
NOP
rjmp RESET
.org 0x12 RETI
.org 0x13
.include "myproc_utilities.inc"
.include "myproc_timer.inc"
;.include "myproc_atmega_serial.inc"


RESET:

init_m8_stack
set_PB_out 0
PB_on 0

REPEAT:
delay_10ms

toggle_PB 0

goto REPEAT
