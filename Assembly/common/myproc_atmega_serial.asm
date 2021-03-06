
; ***** USART ************************
; UDR - USART I/O Data Register
;.equ	UDR0	= 0	; USART I/O Data Register bit 0
;.equ	UDR1	= 1	; USART I/O Data Register bit 1
;.equ	UDR2	= 2	; USART I/O Data Register bit 2
;.equ	UDR3	= 3	; USART I/O Data Register bit 3
;.equ	UDR4	= 4	; USART I/O Data Register bit 4
;.equ	UDR5	= 5	; USART I/O Data Register bit 5
;.equ	UDR6	= 6	; USART I/O Data Register bit 6
;.equ	UDR7	= 7	; USART I/O Data Register bit 7

; UCSRA - USART Control and Status Register A
;.equ	USR	= UCSRA	; For compatibility
;.equ	MPCM	= 0	; Multi-processor Communication Mode
;.equ	U2X	= 1	; Double the USART transmission speed
;.equ	UPE	= 2	; Parity Error
;.equ	PE	= UPE	; For compatibility
;.equ	DOR	= 3	; Data overRun
;.equ	FE	= 4	; Framing Error
;.equ	UDRE= 5	; USART Data Register Empty
;.equ	TXC	= 6	; USART Transmitt Complete
;.equ	RXC	= 7	; USART Receive Complete

; UCSRB - USART Control and Status Register B
;.equ	UCR	= UCSRB	; For compatibility
;.equ	TXB8	= 0	; Transmit Data Bit 8
;.equ	RXB8	= 1	; Receive Data Bit 8
;.equ	UCSZ2	= 2	; Character Size
;.equ	CHR9	= UCSZ2	; For compatibility
;.equ	TXEN	= 3	; Transmitter Enable
;.equ	RXEN	= 4	; Receiver Enable
;.equ	UDRIE	= 5	; USART Data register Empty Interrupt Enable
;.equ	TXCIE	= 6	; TX Complete Interrupt Enable
;.equ	RXCIE	= 7	; RX Complete Interrupt Enable

; UCSRC - USART Control and Status Register C
;.equ	UCPOL	= 0	; Clock Polarity
;.equ	UCSZ0	= 1	; Character Size		1
;.equ	UCSZ1	= 2	; Character Size		1: 8 bits
;.equ	USBS	= 3	; Stop Bit Select		0: 1 stop bit
;.equ	UPM0	= 4	; Parity Mode Bit 0
;.equ	UPM1	= 5	; Parity Mode Bit 1
;.equ	UMSEL	= 6	; USART Mode Select
;.equ	URSEL	= 7	; Register Select

.set serial.LINE_FEED = 10
.set serial.END_OF_TEXT=3


.equ SERIAL_CTRL_A = UCSRA ; bit 6 = transmit complete. set when tranmit is complete. bit 5 = Data register is empty  buffer is empty. 
.equ SERIAL_CTRL_B = UCSRB ; bit 3 = transmit enable. starts the transmit. resets after data register is transfered.
.equ SERIAL_CTRL_C = UCSRC ; bit 2:1. character size for the frame. bit 3 = stop bit size (1 or 2)

.equ SERIAL_BAUD_L = UBRRL
.equ SERIAL_BAUD_H = UBRRH
.equ SERIAL_DATA = UDR

;------------ register direct access -----------
.macro serial.writeControlRegC ; value
	R16_ @0
	out UCSRC, R16
.endm

.macro SERIAL_CTRL_B_;(value)
	R16_ @0
	out SERIAL_CTRL_B, R16
.endm

.macro SERIAL_CTRL_A_;(value)
	R16_ @0
	out SERIAL_CTRL_A, R16
.endm


.macro SERIAL_BAUD_L_;(value)
	R16_ @0
	out SERIAL_BAUD_L, R16
.endm
.macro SERIAL_BAUD_H_;(value)
	R16_ @0
	out SERIAL_BAUD_H, R16
.endm

.macro SERIAL_DATA_;(register)
	out SERIAL_DATA, @0
.endm

.macro SERIAL_TX_ENABLE
	SERIAL_CTRL_B_ 0b00001000
.endm

;------------------------------------ SERIAL INIT -------------------------------
.macro serial_init_16M_9600
	
	; 8 bit character frame, 1 bit stop bit.
	SERIAL_CTRL_C_ 0b10000110

	; UBBR value for 9600 baud for 16MHz
	SERIAL_BAUD_L_ 103

	SERIAL_TX_ENABLE
.endm

.macro serial.init_8M_9600
	
	; 8 bit character frame, 1 bit stop bit.
	serial.writeControlRegC 0b10000110

	; UBBR value for 9600 baud for 16MHz
	SERIAL_BAUD_L_ 51

	SERIAL_TX_ENABLE
.endm

.macro serial_init_16M_76_8K
	; 8 bit character frame, 1 bit stop bit.
	SERIAL_CTRL_C_ 0b10000110

	; UBBR value for 250K baud for 16MHz
	SERIAL_BAUD_L_ 12

	SERIAL_TX_ENABLE

.endm

 .macro serial_init_16M_500K
	; 8 bit character frame, 1 bit stop bit.
	SERIAL_CTRL_C_ 0b10000110

	; UBBR value for 250K baud for 16MHz
	SERIAL_BAUD_L_ 1

	SERIAL_TX_ENABLE

 .endm

;------------------------- serial send data ----------------------
.macro serial.sendRegByte; register
	push R16
	R16__ @0
	rcall _serial_send_data
	pop R16
.endm

.macro serial.sendByte ;value
	push R16
	R16_ @0
	rcall _serial_send_data
	pop R16
.endm

.macro serial.send_R16
	rcall _serial_Send_data
.endm

_serial_send_data: ;(R16)
	_serial_wait:
		if_io_bit_set_skip_next SERIAL_CTRL_A, 5; loop until bit 5 of control register a is set. it indicates that data register is ready to send data and can be written.
	goto _serial_wait
	
	SERIAL_DATA_ R16
ret

;------------------------ serial send string codeseg-----------------------
.macro serial.send_string_cseg;(label)
	csegpointer @0
	rcall _serial_send_string_cseg
.endm

_serial_send_string_cseg:

	_serial_readnext: 
		csegpointer_val_to_R0

	if_register_equal_skip_next R0,0
		goto _serial_send
	ret ; end of string
	_serial_send:
		R16__ R0
		serial.send_R16
		add_int Z,1
	goto _serial_readnext
ret
;------------------------Serial send string async using interrupts --------------------------------

; -- calling this macro will start the async data send with register empty interrupt enabled. use .org 0x00C rcall serial_data_interrupt
.macro serial_string_async;label
	csegpointer @0					; point z to the label
	csetpointer_valto_Z0			; load first byte into Z0
	SERIAL_DATA_ R0					; send first byte
	SERIAL_CONTROL_B_ 0b00100000	; enable data regester empty interrupt
.endm
; 

serial_data_interrupt:; call this macro in the USART register empty interrupt 0x00C address. set Z to the address by using terminate string with 0. example: .org 0x00C rcall serial_data_interrupt

_serial_sendData_async:
	csegpointer_val_to_R0
	
	if_register_equal_skip_next R0,0
		goto _serial_continue
	SERIAL_CTRL_B_ 0; disable interrupt
	reti ; 0, end of string

	_serial_continue:
		SERIAL_DATA_ R0
		ADIW Z,1
reti
;------------------------------------------------------------------------------------------------