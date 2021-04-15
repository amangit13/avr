
;----------------------------------- JUMP CONDITIONS-------------------------------
;---- is register = number
.macro if_register_equal_goto;(register, val, label)
cpi @0,@1 ; compare with immediate
breq @2 ; if Z=0 jump. Z = Zero bit.
.endmacro

.macro goto;(label)
rjmp @0
.endmacro

; not zero goto label
.macro if_flag_not_zero_goto;(lable)
brne @0
.endmacro

.macro if_io_bit_set_skip_next;(io register, bit)
	SBIS @0, @1
.endm

.macro if_register_equal_skip_next;(register, value)
	R16_ @1
	cpse @0,R16
.endm

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


;---------------------- common init -------------------------
.macro init_stack
	R16_ high(RAMEND)
	OUT SPH,R16
	R16_ low(RAMEND)
	OUT SPL, R16
.endm