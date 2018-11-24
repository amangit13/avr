#include <util/delay.h>

#define SND_ENABLE 0x1C, 0x01
#define RESET 0x1C, 0x02

#define OCTAVE01 0x10
#define OCTAVE23 0x11
#define OCTAVE45 0x12

#define FREQ0 0x08
#define FREQ1 0x09
#define FREQ2 0x0A
#define FREQ3 0x0B
#define FREQ4 0x0C
#define FREQ5 0x0D

#define VOL0 0x00
#define VOL1 0x01
#define VOL2 0x02
#define VOL3 0x03
#define VOL4 0x04
#define VOL5 0x05

#define LOAD_ADDR PORTB |= 0b00000001
#define LOAD_DATA PORTB &= 0b11111110

#define WR_H PORTB |=0b00000010
#define WR_L PORTB &=0b11111101
#define _PULSE   {WR_L; delayMicroseconds(5); WR_H;}

void sendCmd(byte unsigned address, byte unsigned command)
{
  LOAD_ADDR;
  Serial.println(PORTB&0x01);
  PORTD = address;
  _PULSE;
  Serial.print("addr "); Serial.println(PORTD, HEX);
  LOAD_DATA;
  PORTD = command;
  _PULSE;
 Serial.println(PORTB&0x01);
  Serial.print("cmd "); Serial.println(PORTD, HEX);
 
}

void initSAA()
{
  Serial.println("begin");
  DDRD = 0xFF;
  DDRB = 0xFF;
  PORTB=0xFF;
  PORTD = 0x00;

  sendCmd(RESET);
  sendCmd(0x1C,0);
  sendCmd(SND_ENABLE);

  sendCmd(0x15,0);
  sendCmd(0x18,0);
  sendCmd(0x19,0);
  Serial.println("init done");
}

void playNote(byte unsigned freq, byte unsigned chan)
{
  sendCmd(OCTAVE01, 0x44);
  sendCmd(FREQ0,173);
  sendCmd(VOL0,0xFF);
  _delay_ms(500);
  sendCmd(RESET);
  
}
