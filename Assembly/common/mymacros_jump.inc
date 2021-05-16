
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


.macro if_reg_bit_set_skip_next ;register, bit
	SBRS @0,@1
.endm

.macro if_reg_zero_goto;(label)
	breq @0
.endm

.macro if_reg_not_zero_goto;(label)
	brne @0
.endm

.macro if_reg_greater_eq_goto ;(reg, value, label)
	cpi @0, @1
	BRSH @2
.endm


