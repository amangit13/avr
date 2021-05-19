;--------------- CONSTANTS --------------
.equ IO_OUTPUT=0
.equ IO_INPUT=1

;-------------------IO PORTB----------------------------
.macro io.PB.setPinMode; (pin #, IO_OUTPUT | IO_INPUT)
.if @1==IO_OUTPUT
	SBI DDRB, @0
.endif
.if @1==IO_INPUT
	CBI DDRB, @0 
.endif
.endm

.macro io.PB.read;(register)
IN @0,PB
.endmacro

.macro io.PB.PinOn;(bit)
SBI PORTB,@0
.endmacro

.macro io.PB.PinOff;(bit)
CBI PORTB,@0
.endmacro

.macro io.PB.togglePin;(bit)
	skip_next_if_PB_bit_set @0
		rjmp _toggle_on
	io.PB.PinOff @0
	rjmp _return1
_toggle_on:
	io.PB.PinOn @0

_return1:
.endmacro


.macro skip_next_if_PB_bit_set;(bit)
SBIS PORTB,@0					; skip if bit # set		
.endmacro				


;---------------------- bit operations IO -----------------------
.macro io.setPin;(port, bit)
	sbi @0,@1
.endm

;----------------------- direct port access-------------------------

.macro DDRB_ ;value
	push R16
	R16_ @0
	out DDRB, R16
	pop r16
.endm

.macro _DDRB; register
	IN @0, DDRB
.endm

.macro PORTB_ ; value
	push R16
	R16_ @0
	out PORTB, R16
	pop R16
.endm

.macro _PORTB; register
	in @0, PORTB
.endm

.macro _PINB; register
	in @0, PINB
.endm
