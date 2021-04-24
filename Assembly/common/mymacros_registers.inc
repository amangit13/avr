;--------------------------REGISTER ASSIGNMENTS------------------------------------
.macro R0_ 
ldi r0,@0 
.endm
.macro R1_ 
ldi r1,@0
.endm
.macro R2_ 
ldi r2,@0 
.endm
.macro R3_ 
ldi r3,@0 
.endm
.macro R4_ 
ldi r4,@0 
.endm
.macro R5_ 
ldi r5,@0 
.endm
.macro R6_ 
ldi r6,@0 
.endm
.macro R7_ 
ldi r7,@0 
.endm
.macro R8_ 
ldi r8,@0 
.endm
.macro R9_ 
ldi r9,@0 
.endm
.macro R10_ 
ldi r10,@0 
.endm
.macro R11_ 
ldi r11,@0 
.endm
.macro R12_ 
ldi r12,@0 
.endm
.macro R13_ 
ldi r13,@0 
.endm
.macro R14_ 
ldi r14,@0 
.endm
.macro R15_ 
ldi r15,@0 
.endm

.macro R16_
	ldi r16,@0
.endmacro

.macro R16_R
mov r16,@0
.endm

.macro R17_
ldi r17,@0
.endmacro

.macro R18_
ldi r18,@0
.endm

.macro R19_
ldi r19,@0
.endmacro

.macro R20_
ldi r20,@0
.endmacro

.macro R21_
ldi r21,@0
.endm

.macro R22_
ldi r22,@0
.endm
.macro R23_
ldi r23,@0
.endm
.macro R24_
ldi r24,@0
.endm
.macro R25_
ldi r25,@0
.endm
.macro R26_
ldi r26,@0
.endm
.macro R27_
ldi r27,@0
.endm
.macro R28_
ldi r28,@0
.endm
.macro R29_
ldi r29,@0
.endm
.macro R30_
ldi r30,@0
.endm
.macro R31_
ldi r31,@0
.endm


;-------------------IO PORTB----------------------------
.macro set_PB_out;(bit) set direction
SBI DDRB, @0
.endmacro

.macro set_PB_in;(bit) setdirection
SBI DDRB, @0
.endmacro

.macro read_PB0;(register)
IN @0,PB0
.endmacro

.macro PB_on;(bit)
SBI PORTB,@0
.endmacro

.macro PB_off;(bit)
CBI PORTB,@0
.endmacro

.macro skip_next_if_PB_bit_set;(bit)
SBIS PORTB,@0					; skip if bit # set		
.endmacro				

.macro toggle_PB;(bit)
	skip_next_if_PB_bit_set @0
		rjmp _toggle_on
	PB_off @0
	rjmp _return1
_toggle_on:
	PB_on @0

_return1:
.endmacro

;---------------------- bit operations IO -----------------------
.macro set_io_bit;(io, bit)
	sbi @0,@1
.endm