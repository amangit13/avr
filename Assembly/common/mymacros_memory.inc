;------------------ variables, constants and eeprom macros
.macro PointAtProgConst;(label)
	LDI ZH, high(@0*2)
	LDI ZL, low(@0*2)
.endm

.macro LoadValueOfProgConst_R0
	LPM
.endm
