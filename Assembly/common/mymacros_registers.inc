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

.macro R16__
mov r16,@0
.endm

.macro R17_
ldi r17,@0
.endmacro

.macro R17__
	mov R17,@0
.endm

.macro R18__
	mov R18,@0
.endm
.macro R18_
ldi r18,@0
.endm

.macro R19_
ldi r19,@0
.endmacro

.macro R19__
	mov R19, @0
.endm

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

.macro R24__
	Mov R24, @0
.endm

.macro R25_
	ldi r25,@0
.endm

.macro R25__
	Mov R25, @0
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

;--------------- word read and write ops -------------------
.macro set_word_to_reg; register, 16 bit val. Rn:Rn+1 = int
	ldi @0, low(@1)
	ldi @0+1, high(@1)
.endm

.macro set_word_to_port; port, 16 bit val. Pb:Pn+1 = int
	ldi R16, low(@1)
	ldi R17, high(@1)
	out TCNT1L, R16
	out TCNT1H, R17
.endm

.macro register.setBit;(register, bit #)
	sbr @0,@1
.endm


