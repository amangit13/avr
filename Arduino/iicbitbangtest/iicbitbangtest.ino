//#define F_CPU 16000000;
#include <util/delay.h>
#define NOP __asm__("nop\n\t")
#define SDA_H PORTC |= (1<<4)
#define SDA_L PORTC &= ~(1<<4)
#define SCK_H PORTC |= (1<<5)
#define SCK_L PORTC &= ~(1<<5)

#define SCK_IN DDRC &= ~(1<<5)
#define SCK_OUT DDRC |= (1<<5)

#define SDA_IN DDRC &= ~(1<<4)
#define SDA_OUT DDRC |= (1<<4)

#define SCK_read PINC & (1<<5)
#define SDA_read PINC & (1<<4)

#define dly _delay_ms(5)
void I2CStart()
{
  SDA_H;
  SCK_H;
  dly;
  SDA_L; // start trigger
  dly;
  SCK_L;
  
}

void I2CStop()
{
  SCK_L;
  SDA_L;
  dly;
  SCK_H; // stop trigger
  dly;
  SDA_H;
}

void I2CWrite()
{
  byte unsigned data = 0;
  dly;
  // write 0xC0 address
  for (byte i = 7; i==0; i--)
  {
    if (0x0A & (1<< i))
      SDA_H;
    else
      SDA_L;
    
    dly;
    SCK_H;
    dly;
    SCK_L;
  }

  SDA_IN; // switch to read ack
  SCK_IN;

  while (SCK_read == 0); // clock stretch
  
  dly;
    
  SCK_H;
  dly;   
  data = SDA_read;
  dly;
  SCK_L;

  dly;
  SDA_OUT; // swtich back to output

  if (data)
    Serial.println("success");
  else
    Serial.println ("fail");

}

void setup() {
  // put your setup code here, to run once:
  //setup PC4 and PC5 as output to bit bang SDA and SCL respectively on UNO 3

  Serial.begin(9600);
  SDA_OUT;
  SCK_OUT;

  Serial.println("starting");
  I2CStart();
  I2CWrite();
  I2CStop();
  Serial.println("done");
 
}

void loop() {
  // put your main code here, to run repeatedly:

}
