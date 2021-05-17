;
; SETDirectiveTest.asm
;
; Created: 5/16/2021 10:11:32 PM
; Author : amana
;


; Replace with your application code
start:
    .set _v1=0xAD
	LDI R16, _v1
	.set _v1=0xBB
	LDI R16,_v1
    rjmp start
