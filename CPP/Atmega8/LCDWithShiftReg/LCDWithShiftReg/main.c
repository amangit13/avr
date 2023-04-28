/*
 * LCDWithShiftReg.c
 *
 * Created: 4/25/2023 8:54:08 PM
 * Author : aman
 */ 
#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>


	/*
		atmega8 to shift register. RCLK to inverter to latch to drive clock using same port.
		drive lcd using shift register
		use 4 bit mode to drive data and control lines of lcd
		3 chips needed
		1. shift register
		2. hex inverter to invert clk signal for latch
		3. atmega8
		
		shift register connected to lcd control and 4 data pins. 
		2 most significant bits used for RS and EN
		Frame format is
		X X RS E d7 d6 d5 d4	
	
	*/
#define DEBUG_LED 1<<PORTB1
#define SER 1<<PORTD7
#define CLK 1<<PORTD6
#define SERIALPORT PORTD
#define LATCH 1<<PORTD5

void sendSerial (uint8_t data)
{
	for (int i=7; i>=0;i--)
	{
			if (data&1<<i) // send most significant bit first
				SERIALPORT |= SER;
			else
				SERIALPORT &= ~SER;
				
			SERIALPORT |= CLK;
			SERIALPORT &= ~CLK;
	}
	
	SERIALPORT |= LATCH;
	SERIALPORT &= ~LATCH;

}

void sendCommand4bit(uint8_t cmd)
{

//X X RS E d7 d6 d5 d4

// reset everything
sendSerial(0x00);

// send high bits. Enable On
sendSerial(0b00010000 | (0x0F & cmd>>4));

// send high bits. Enable Off
sendSerial(0b00000000 | (0x0F & cmd>>4));

// send low bits. Enable On
sendSerial(0b00010000 | (0x0F & cmd));

// Send low bit, enable off
sendSerial(0b00000000 | (0x0F & cmd));


	
}

void sendData4bit(uint8_t data)
{
	//X X RS E d7 d6 d5 d4
	
	// reset everything
	sendSerial(0x00);

	// send high bits. Enable On
	sendSerial(0b00110000 | (0x0F & data>>4));

	// send high bits. Enable Off
	sendSerial(0b00100000 | (0x0F & data>>4));

	// send low bits. Enable On
	sendSerial(0b00110000 | (0x0F & data));

	// Send low bit, enable off
	sendSerial(0b00100000 | (0x0F & data));


}


void initlcd()
{
	// set 4 bit
	sendCommand4bit(0b0010000);
	
	// clear display
	sendCommand4bit(0b00000001);
	
	// cursor home
	sendCommand4bit(0b00000010);
	
	// screen on, cursor off
	sendCommand4bit(0b00001100);
	
}




int main(void)
{
	DDRB = 0XFF;
	DDRD = 0XFF;
	PORTB = 0X00;
	PORTD = 0X00;
	
	initlcd();
	sendData4bit('A');
	
	
    while (1) 
    {
	
		PORTB |= DEBUG_LED;		
		_delay_ms(500);
		
		PORTB &= ~DEBUG_LED;		
		_delay_ms(500);
		
    }
}

