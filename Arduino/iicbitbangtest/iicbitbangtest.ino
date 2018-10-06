//#define F_CPU 16000000;
#include <util/delay.h>
#define NOP __asm__("nop\n\t")
#define SDA_H PORTC |= (1<<4)
#define SDA_L PORTC &= ~(1<<4)
#define SCK_H PORTC |= (1<<5)
#define SCK_L PORTC &= ~(1<<5)

#define SCK_IN DDRC &= ~(1<<5)
#define SCK_OUT DDRC |= (1<<5);
#define SDA_IN DDRC &= ~(1<<4)
#define SDA_OUT DDRC &= ~(1<<4)

#define SCK PINC & (1<<5)
#define SDA PINC & (1<<4)

void I2CStart()
{
  SDA_H;
  SCK_H;
  SDA_L;
  SCK_L;
  
}

void I2CStop()
{
  SCK_L;
  SDA_L;
  SCK_H;
  SDA_H;
}

void I2CWrite()
{
  // write 0xC0 address
  for (byte i = 0; i<8; i++)
  {
    if (0xC0 & (1<< i))
      SDA_H;
    else
      SDA_L;

      SCK_H;
      SCK_L;
  }

  SCK_H;
  SCK_IN; // switch to read port SCK

  while (SCK); // reading sck from slave. wait for it to go low.
  
  if (SDA)
    Serial.println("success");
  else
    Serial.println ("fail");

  SDA_OUT;
  SCK_OUT;
  SCK_L;
}

void setup() {
  // put your setup code here, to run once:
  //setup PC4 and PC5 as output to bit bang SDA and SCL respectively on UNO 3

  DDRC |= (1<<4) | (1<<5);

}

void loop() {
  // put your main code here, to run repeatedly:

}
