/*
 * Blink.c
 *
 * Created: 4/23/2023 8:20:58 PM
 * Author : amana
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#define RS PORTB1
#define EN PORTB2
#define LED PORTB0


uint8_t string[32] = {"hello world, lcd <<<< >>>>> ...."};

void sendCmd(unsigned char cmd)
{
	PORTB &= ~ 1 << EN;
	PORTB &= ~(1<<RS); // RS low for command
	PORTD = cmd;

	PORTB |= 1<< EN;
		
	_delay_us(500);
	PORTB &= ~ 1 << EN;
	_delay_us(500);
}

void sendData(unsigned char data)
{
	PORTB &= ~ 1 << EN;
	_delay_us(500);
	PORTB |= (1<<RS); // RS high for data
	_delay_us(500);
	PORTD = data;
	PORTB |= 1<< EN;
	_delay_us(500);
	PORTB &= ~ 1 << EN;
	_delay_us(500);
	
}

void sendStr (uint8_t * chars, unsigned char len)
{
	for (unsigned char i = 0; i< len; i++)
	{
		sendData(chars[i]);
	}
}

int main(void)
{
    /* Replace with your application code */
	DDRD = 0XFF;
	PORTD = 0x00;

	DDRB = 0XFF;
	PORTB = 0X00;

	_delay_ms(500);
// switch on the lcd
	
	// https://www.sparkfun.com/datasheets/LCD/ADM1602K-NSW-FBS-3.3v.pdf
	sendCmd(0b00111100);// 8 bit 2 line. 1 DL N F -  -
	sendCmd(0b00000001); // clear screen
	sendCmd(0b00000010); // return home
	sendCmd(0b00001100); // display on, no cursor.  0 0 0 0 1 D C B 
	
	sendStr(string, 32); /// send text !!!!!!!!!!!!!!!!!!!!!!!
	
    while (1) 
    {
		PORTB ^= 0X01;
		//PORTB |= 1 << LED;
		_delay_ms(400);
		sendCmd(0b00011000); // shift display left
		
		//PORTB &= ~1 << LED;
		//_delay_ms(500);

    }
}

