;-------------------- timer related macros and functions
.macro begin_m_timer0
	R16_ 0
	out TCNT0, R16 ; set timer counter to 0
	R16_ 5; pre scale div by 1024
	out TCCR0, R16
.endm

.macro stop_m_time0
	R16_ 0
	out TCCR0, R16
.endm

.macro delay_m_timer0_msec
	rcall _delay_m_timer0_msec
.endm

_delay_m_timer0_msec:	
	
	begin_m_timer0()

	_delay_wait:
		IN R16,TIFR
			if_reg_bit_set_skip_next R16, 0 ; bit 1 is timer over flow bit
		goto _delay_wait ; bit not set loop back
	
	// reset flag
	R16_ 1 ; setting bit 1 resets the overflow flag
	out TIFR, R16
	stop_m_time0
ret

;-------------------------- Timer 1 ---------------------------------------------------

;------------------- Access Regiters Timer1.Counter, Timer1.Flags, etc ----------------
;timer1
	.macro timer1.readCounter ; (reg:reg+1)
		IN @0,TCNT1L
		IN @1,TCNT1H
	.endm

	.macro timer1.readFlagReg ; register
		in @0, TIFR
	.endm

	.macro timer1.writeFlagReg ; value
		R16_ @0
		out TIFR, R16
	.endm

	.macro timer1.writeControlRegA; value
		R16_ @0
		out TCCR1A, R16
	.endm

	.macro timer1.writeControlRegB; value
		R16_ @0
		out TCCR1B, R16
	.endm

	.macro timer1.readControlAReg; Reg
		in @0,TCCR1A
	.endm

	.macro timer1.readControlBReg; reg
		in @0, TCCR1B
	.endm

;timer1.controlReg
				.macro timer1.controlReg.setPrescalar; val
					R16_ @0
					out TCCR1B, R16
				.endm

;---------------------------------------------------------------------------------------

.macro timer1.begin
	set_word_to_port TCNT1L,0
	timer1.controlReg.setPrescalar 5
	timer1.writeFlagReg 1<<TOV1
.endm

.macro timer1.stop
	timer1.controlReg.setPrescalar 0
.endm

.macro timer1.delay_msec
	rcall _timer1_delay_msec
.endm
.macro timer1.begininterrupt
	timer1.controlReg.setPrescalar 2
	R16_ 1<<TOIE1
	out TIMSK, R16
.endm
_timer1_delay_msec:
	timer1.begin

	_delay_timer1:
		timer1.readFlagReg R16
		if_reg_bit_set_skip_next R16, 1<<TOV1
			goto _delay_timer1

ret

.macro timer1.interruptHandler
.org 0x003 rcall _timer_interrupt
.endm
