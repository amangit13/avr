;
; ASMTest.asm
;
; Created: 3/15/2021 8:43:01 PM
; Author : amana
;


; Replace with your application code
ldi r16,250
sbi DDRB, 4
nop
start:
    inc r16
    rjmp start
