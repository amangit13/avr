#include<io.h>

#define wait_IIC  while (!(TWCR & 1<< TWINT)) 

void setup() {
  // put your setup code here, to run once:
  DDRC = 0xff;
  Serial.being(9600);
  
  // 100Khz. TWBR 72. leave TWSR as is for prescalar of 1. first two bits zero
  TWBR = 72;
  TWSR &= 0b11111100;


  // start bit
  // enable TWI
  TWCR |= 1<<TWEN;
  // transmit start bit
  TWCR |= 1<<TWSTA;
  // start transmitting by clearing interrupt flag
  TWCR |= 1<<TWINT;

  wait_IIC;

  // send dummy address
  TWDR = 0x0a; //wrong address write mode. looking for nack
  TWCR |= ((1<< TWEN) | (1<<TWINT));
  wait_IIC;


  if ((TWSR & 0xF8) == 0x20)
  {
    // error
    Serial.print ("nack recieved");
    // send data
  }
  else
  {
    Serial.println("ack recieved");
    // send data
  }

  
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
