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
  SCK_H;
  dly;
  SDA_L; // start trigger
  dly;
  
}

void I2CStop()
{
  SCK_H;
  dly;
  SDA_H;
  dly;
}

void I2CWrite()
{
  byte unsigned data = 0;

  // 0xC0 is the correct address. write anyting else to get nack and 0xc0 to get ack.
  for (byte i = 7; i>=1; i--)
  {
    if (0b01010100 & (1<< i))
      SDA_H;
    else
      SDA_L;
    
    dly;
    SCK_H;
    dly;
    SCK_L;
    dly;
  }

  // master sending data. write mode bit.
  SDA_L;
  SCK_H;
  dly;
  SCK_L;
  dly;

  // pull high before reading the ack.
  SDA_H;
  
  // switch data to input to read ack
  SDA_IN;
  SCK_H;
  dly;
  SCK_L;
  dly;
   // read ack
  data = SDA_read;
  dly;
  
  SDA_OUT; // swtich back to output
  dly;
  SDA_L;
  
  if (data)
    Serial.println("fail");
  else
    Serial.println ("success");

}

void I2CInit()
{
  SDA_OUT;
  SCK_OUT;
  SDA_H;
  SCK_H;
  Serial.println(SDA, BIN);
  Serial.println(SCK, BIN);
  
}
void setup() {
  // put your setup code here, to run once:
  //setup PC4 and PC5 as output to bit bang SDA and SCL respectively on UNO 3

  Serial.begin(9600);
  I2CInit();
  
  Serial.println("starting");
  I2CStart();
  I2CWrite();
  I2CStop();
  Serial.println("done");
 
}

void loop() {
  // put your main code here, to run repeatedly:

}
