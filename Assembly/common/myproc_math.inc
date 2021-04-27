
.macro subtract_int; [R24..30], int. subtract_int R24, 2000
	SBIW @0, @1
.endm

.macro add_int ; [R24..30], int
	ADIW @0, @1
.endm