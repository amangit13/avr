.macro string.hexToStr_R18R19;(uses R18:R19 = R18) converts hex value of R18 into two chars stored in R18 and R19. 
	rcall _hex_to_str
.endm

_hex_to_str:
	R19__ R18			; copy
	
	Push R16			; temp vars
	Push R17

	ANDI R18, 0x0F		; R18 contains lower half of hex
	SWAP R19			; R19 swp nibbles. lower half now contains upper half bits
	ANDI R19, 0x0F		; R19 now contains lower half of hex

	; handle R18
	if_reg_greater_eq_goto R18, 10, _hex_to_str_setR16_55
		R16_ 48
		goto _hex_to_str_handleR19
	
		_hex_to_str_setR16_55:
			R16_ 55

	_hex_to_str_handleR19:
		if_reg_greater_eq_goto R19, 10, _hex_to_str_setR17_55
			R17_ 48
			goto _hex_to_str_add

			_hex_to_str_setR17_55:
				R17_ 55

	_hex_to_str_add:
		ADD R18, R16
		Add R19, R17
	
	POP R16
	POP R17
ret