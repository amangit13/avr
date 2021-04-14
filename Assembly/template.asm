#define _ATMEGA8_
.include "C:\Files\AVR\Assembly\common\mymacros_registers.inc"
.include "C:\Files\AVR\Assembly\common\mymacros_jump.inc"
.include "C:\Files\AVR\Assembly\common\mymacros_memory.inc"
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

.include "C:\Files\AVR\Assembly\common\myproc_utilities.inc"
.include "C:\Files\AVR\Assembly\common\myproc_atmega_serial.inc"
goto RESET


RESET:
    goto RESET