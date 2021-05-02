#define _9_6MHZ_
.include "mymacros_registers.inc"
.include "mymacros_jump.inc"
.include "mymacros_memory.inc"
.include "mymacros_io.inc"
.dseg


.cseg
.org 000 goto RESET
.org 0x12 RETI

.org 0x13
.include "myproc_math.inc"
.include "myproc_utilities.inc"
.include "myproc_atmega_timer.inc"
.include "myproc_atmega_serial.inc"

RESET:

init_m8_stack
serial.init_8M_9600
io.PB.setPinForOutput 0
io.PB.PinOn 0

timer1.begin()

MAIN_REPEAT:
	//timer1.readCounter R16, R17
	//serial.send_R16
	//serial.sendRegByte R17
	//serial.sendByte 32
	timer1.readFlagReg R16
	serial.send_R16
	io.PB.togglePin 0

goto MAIN_REPEAT
