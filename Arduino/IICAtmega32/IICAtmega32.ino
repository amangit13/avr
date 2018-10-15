
//#include <Wire.h>
#define wait_IIC  while (!(TWCR & (1<< TWINT))) 

void setup() {
  // put your setup code here, to run once:
  DDRC = 0xff;
  PINC = 0xff; // enable pullups
  Serial.begin(9600);
  
  // 100Khz. TWBR 72. leave TWSR as is for prescalar of 1. first two bits zero
  TWBR = 72;
  TWSR &= 0b11111100;


  // start bit
  TWCR |= ((1<<TWEN) | (1<<TWSTA) | (1<<TWINT));
  wait_IIC;

  // send dummy address
  TWDR = 0x3C; //
  TWCR |= ((1<< TWEN) | (1<<TWINT));
  wait_IIC;

  if ((TWSR & 0xF8) == 0x20)
  {
    // error
    Serial.println ("nack recieved");
    // send data

    // send stop bit
    TWCR = ((1<<TWEN)|(1<<TWINT)|(1<<TWSTO));
    Serial.println("stop bit sent");
  }
  else
  {
    Serial.println("ack recieved");
    // send dummy data
    TWDR = 0; //
    TWCR |= ((1<<TWEN)|(1<<TWINT));
    wait_IIC;

    // send stop bit
    TWCR = ((1<<TWEN)|(1<<TWINT)|(1<<TWSTO));
    Serial.println("done dummy date. stop bit sent");
    
  }

  
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
