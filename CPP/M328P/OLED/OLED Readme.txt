OLED	DES	PIN	PORT
----	---	---	---
DC	DC	27	PC5
CS	CS	28	PC4
Res	RES	26	PC3

D0	CLK	19	PB5
D1	MOSI	17	PB3

displays bars on the oled screen. 
!!! Requires 5V and GND connections !!!



http://asciiflow.com/

     1    +----------+  28 PC5 +------+  CS +------+	
     2    |          |  27 PC4 +------+  DC |      |
     3    |          |  16 PC3 +------+ RST |      |
     4    |          |  25                  |oled  |
     5    |          |  24                  |      |
     6    |          |  23                  |      |
vcc  7    |atmega328p|  22 gnd              |      |
gnd  8    |          |  21                  |      |
     9    |          |  20 VCC              |      |
     10   |          |  19 PB5 SCK +---+ D0 |      |
     11   |          |  18                  |      |
     12   |          |  17 PB3 MOSI +--+ D1 |      |
     13   |          |  16                  +------+
     14   +----------+  15 --- used by tone generator
