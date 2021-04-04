;--------------------------REGISTER ASSIGNMENTS------------------------------------

.macro R16_
ldi r16,@0
.endmacro

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
.endmacro

;----------------------------------- JUMP CONDITIONS-------------------------------
;---- is register = number
.macro is_equal_goto;(register, val, label)
cpi @0,@1 ; compare with immediate
breq @2 ; if Z=0 jump. Z = Zero bit.
.endmacro

.macro goto;(label)
rjmp @0
.endmacro

; not zero goto label
.macro not_zero_goto;(lable)
brne @0
.endmacro

; ------------------------------- loops -----------------------------------------
; while not zero. R16 --
.macro repeat_until_r16_0;(label)
dec R16			; 1
brne @0			; 1 when false, 2 when true
.endmacro

; while not zero. R17 --
.macro repeat_until_r17_0;(label)
dec R17
brne @0					; jump to label if not zero
.endmacro

.macro repeat_until_r16;(val, label)
inc R16
cpi R16,@0			; if R16 == val
breq @1				; jump to label if not zero
.endmacro

.macro rpeat_until_r17;(val, label)
inc R17
cpi R17,@0			; if R17 == val
breq @1				; jump to label
.endm

.macro repeat_until;(Register,Nnumber, label)
inc @0
cpi @0,@1
brne @2
.endm

;------------------------- EQUAL assignemnts ----------------------------------
.macro EQ;(Register, val) R16 = value at ram address e.b., R16 = @(22). 
LDS @0,@1
.endmacro

;-------------------IO----------------------------
.macro SET_PB_OUT
SBI DDRB, @0 ; DDRB_ 1
.endmacro

.macro SET_PB_IN
SBI DDRB, @0 ; DDRB_ 1
.endmacro

.macro READ_PB0
IN @0,PB0
.endmacro

;--------------- PORTB ------------------
.macro PB_ON ; PB_ON 1
SBI PORTB,@0
.endmacro

.macro PB_OFF ; PB_Off 1
CBI PORTB,@0
.endmacro

.macro IF_PB_BIT_SET_SKIP	; if_PB_BIT_SET 1 
SBIS PORTB,@0			
.endmacro				

.macro TOGGLE_PB
	IF_PB_BIT_SET_SKIP @0
		rjmp _ON
	PB_OFF @0
	rjmp _return1
_ON:
	PB_ON @0

_return1:
.endmacro

