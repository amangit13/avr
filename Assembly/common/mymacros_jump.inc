
;----------------------------------- JUMP CONDITIONS-------------------------------
;---- is register = number
.macro if_reg_equ_goto;(register, val, label)
cpi @0,@1 ; compare with immediate
breq @2 ; if Z=0 jump. Z = Zero bit.
.endmacro

.macro goto;(label)
rjmp @0
.endmacro

; not zero goto label
.macro if_not_zero_goto;(lable)
brne @0
.endmacro

.macro if_io_bit_set_skip_next;(io register, bit)
	SBIS @0, @1
.endm

.macro if_register_equal_skip_next;(register, value)
	R16_ @1
	cpse @0,R16
.endm


.macro if_reg_zero_goto;(label)
	breq @0
.endm

.macro if_reg_not_zero_goto;(label)
	brne @0
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

.macro repeat_until_equ;(Register,Nnumber, label)
inc @0
cpi @0,@1
brne @2
.endm


