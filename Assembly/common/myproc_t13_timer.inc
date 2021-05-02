;-------------------- timer related macros and functions
.macro begin_t13_timer0
	R16_ 0
	out TCNT0, R16
	R16_ 5; pre scale div by 1024
	out TCCR0B, R16
.endm

.macro stop_t13_time0
	R16_ 0
	out TCCR0B, R16
.endm

.macro delay_t13_timer_msec
	rcall _delay_t13_timer_msec
.endm

_delay_t13_timer_msec:	
	begin_at13_timer0
	_delay_wait:
		IN R16,TIFR0
			if_reg_bit_set_skip_next R16, 1 ; bit 1 is timer over flow bit
		goto _delay_wait ; bit not set loop back
	
	// reset flag
	R16_ 2 ; setting bit 1 resets the overflow flag
	out TIFR0, R16
	stop_at13_time0
ret