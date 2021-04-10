;UCSRC
;UCSRC – USART Control and Status Register C
;URSEL: 
; Bit 7 – URSEL: Register Select
; Bit 6 – UMSEL: USART Mode Select
;
;
.equ SERIAL_CTRL_A = UCSRA ; bit 6 = transmit complete. set when tranmit is complete. bit 5 = Data register is empty  buffer is empty. 
.equ SERIAL_CTRL_B = UCSRB ; bit 3 = transmit enable. starts the transmit. resets after data register is transfered.
.equ SERIAL_CTRL_C = UCSRC ; bit 2:1. character size for the frame. bit 3 = stop bit size (1 or 2)

.equ SERIAL_BAUD_L = UBRRL
.equ SERIAL_BAUD_H = UBRRH

.equ SERIAL_DATA = UDR

.macro SERIAL_CTRL_C_;(register)
	out SERIAL_CTRL_C, @0
.endm

.macro SERIAL_CTRL_B_;(regsiter)
	out SERIAL_CTRL_B, @0
.endm

.macro SERIAL_CTRL_A_;(register)
	out SERIAL_CTRL_A, @0
.endm


.macro SERIAL_BAUD_L_;(register)
	out SERIAL_BAUD_L, @0
.endm
.macro SERIAL_BAUD_H_;(register)
	out SERIAL_BAUD_H, @0
.endm

.macro SERIAL_DATA_;(register)
	out SERIAL_DATA,@0
.endm

.macro SERIAL_TX_ENABLE
	R16_ 0b00001000
	SERIAL_CTRL_B_ R16
.endm


.macro serial_init_16M_9600
	R16_ 103; UBBR value for 9600 baud for 16MHz
	SERIAL_BAUD_L_ R16
	R16_ 0b00000110 ; 8 bit character frame, 1 bit stop bit.
	SERIAL_CTRL_C_ r16
.endm

.macro serial_send_data ;(value)
	serial_wait:
		if_bit_set_skip_next SERIAL_CTRL_A, 5; loop until bit 5 of control register a is set. it indicates that data register is ready to send data and can be written.
	rjmp serial_wait

	R16_ @0
	SERIAL_DATA_ R16
	SERIAL_TX_ENABLE

.endm