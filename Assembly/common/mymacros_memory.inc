;------------------ variables, constants and eeprom macros
.macro csegpointer
	LDI ZH, high(@0*2)
	LDI ZL, low(@0*2)
.endm

.macro csegpointer_val_to_R0
	LPM
.endm

.macro readcseg_to_r0
	csegpionter
	LPM
.endm

;------------------------- SRAM variable assignemnts ----------------------------------
.macro set_var;(variable, register) var1 = R16
STS @0,@1
.endm

.macro read_var;(register, variable)
LDS @0,@1
.endm


;---------------- constants in cseg -------------------


;---------------------- stack init -------------------------
.macro init_m8_stack
	R16_ high(RAMEND)
	OUT SPH,R16
	R16_ low(RAMEND)
	OUT SPL, R16
.endm


.macro init_t13_stack
	R16_ low(RAMEND)
	OUT SPL, R16
.endm


;------------------- hepful macros ----------------------------
.macro push3; reg, reg, reg
push @0
push @1
push @2
.endm

.macro pop3 ; reg,reg, reg
pop @0
pop @1
pop @2
.endm

.macro push2; reg,reg
push @0
push @1
.endm

.macro pop2; reg,reg
pop @0
pop @1
.endm



