.include "mymacros_registers.inc"
.include "mymacros_jump.inc"
.include "mymacros_memory.inc"
.include "mymacros_io.inc"
.include "mymacros_math.inc"

; Replace with your application code
MAIN:
	;mem.loadConst cvar1, R16,R17
	 
goto MAIN

.cseg
cvar1:.DB 1,2


.dseg
var1: .byte 1

.eseg
var2: .byte 1