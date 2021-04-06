;---------------------------------- DLY ------------------------------------------
delay_1_sec:; for attiny13 running at 9.6 Mhz
R18_ 0
R16_ 255
R17_ 255

dly_r18:
	dly_r16:
		dly_r17: 
		repeat_until_r17_0 dly_r17
	repeat_until_r16_0 dly_r16
repeat_until R18,48,dly_r18
RET
