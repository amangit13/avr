
;----------------------------------- JUMP CONDITIONS-------------------------------
;---- is register = number
.macro is_equal;(register, val)
cpi @0,@1 ; compare with immediate
.endmacro

	.macro yes_equal_goto;(label)
	breq @0 ; if Z=0 jump. Z = Zero bit.
	.endmacro

	.macro not_equal_goto;(label)
	brne @0 ; if not eqal jump
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
.macro dec_while_R16_not_0;(label)
dec R16
brne @0
.endmacro

; while not zero. R17 --
.macro dec_while_R17_not_0;(label)
dec R17
brne @0					; jump to label
.endmacro


.macro dec_R16_until ; dec_R16_until (val, label)
dec R16
cpi R16,@0			; if R16 == val
breq @1				; jump to label
.endmacro

.macro dec_R17_until ; dec_R17_until (val, label)
dec R17
cpi R17,@0			; if R17 == val
breq @1				; jump to label
.endmacro


;--------------------------REGISTER ASSIGNMENTS------------------------------------

.macro R16_
ldi r16,@0
.endmacro

.macro R17_
ldi r17,@0
.endmacro

.macro R19_
ldi r19,@0
.endmacro

.macro R20_
ldi r20,@0
.endmacro

.macro R21_
ldi r21,@0
.endmacro

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

.macro IF_PB_BIT_SET	; if_PB_BIT_SET 1 
SBIS PORTB,@0			;	PB_OFF 1
.endmacro				; PB_ON 1

.macro TOGGLE_PB
	IF_PB_BIT_SET @0
		rjmp _ON
	PB_OFF @0
	rjmp _return1
_ON:
	PB_ON @0

_return1:
.endmacro