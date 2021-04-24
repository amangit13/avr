;------------------ variables, constants and eeprom macros
.macro PointAtProgConst;(label)
	LDI ZH, high(@0*2)
	LDI ZL, low(@0*2)
.endm

.macro LoadValueOfProgConst_R0
	LPM
.endm

.macro csegpointer
	LDI ZH, high(@0*2)
	LDI ZL, low(@0*2)
.endm

.macro csegpointer_val_to_R0
	LPM
.endm


;------------------------- SRAM variable assignemnts ----------------------------------
.macro set_var;(variable, register) R16 = value at ram address e.b., R16 = @(22). 
STS @0,@1
.endm

.macro read_var;(register, variable)
LDS @0,@1
.endm

;---------------------- common init -------------------------
.macro init_m8_stack
	R16_ high(RAMEND)
	OUT SPH,R16
	R16_ low(RAMEND)
	OUT SPL, R16
.endm