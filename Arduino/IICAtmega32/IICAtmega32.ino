
//#include <Wire.h>
#define twi_wait  while (!(TWCR & (1<< TWINT))) 
#define twi_start   TWCR |= ((1<<TWEN) | (1<<TWSTA) | (1<<TWINT))
#define twi_stop     TWCR = ((1<<TWEN)|(1<<TWINT)|(1<<TWSTO))
#define twi_senddata   TWCR |= ((1<< TWEN) | (1<<TWINT))
#define twi_status (TWSR & 0xF8)
#define twi_nack 0x20
#define twi_setdata(X) TWDR = X

#define twi_ret_on_nack   if (twi_status == twi_nack)\
  {\
    twi_stop;\
    return;  \
  }

 
#define uint8 byte unsigned

void sendCommand(uint8 command)
{
  twi_start;
  twi_wait;
  twi_setdata = 0x3D;
  twi_sendata;
  twi_wait;
  twi_ret_on_nack

  twi_setdata = 0; // control
  twi_senddata;
  twi_ret_on_nack;

  twi_setdata = command;
  twi_senddata;
  twi_stop;
  
}


void oled_begin()
{
  DDRC = 0xff;
  PINC = 0xff;
  
  twi_start;
  twi_wait;
  twi_setdata = 0x3D;
  twi_senddata;
  twi_ret_on_nack;
  sendCommand(0xae); // display off
    
 
}



void setup() {
  // put your setup code here, to run once:
  DDRC = 0xff;
  PINC = 0xff; // enable pullups
  Serial.begin(115200);
  
  // 400Khz. TWBR 12 for 400Khz, or 72 for 100Khz. leave TWSR as is for prescalar of 1. first two bits zero
  TWBR = 12;
  TWSR &= 0b11111100;

  Serial.println("start");
 
  // start bit
  twi_start;
  twi_wait;

  Serial.print("status ");   Serial.println(TWSR);
  
  // send address
  twi_setdata = 0x3D; //
  twi_senddata;
  twi_wait;

  if (twi_status == 0x20)
  {
    // error
    Serial.println ("nack recieved");
    // send stop bit
    twi_stop;
    Serial.println("stop bit sent");
  }
  else
  {
    Serial.println("ack recieved");
    // send dummy data
    twi_setdata = 0; //
    twi_senddata;
    twi_wait;

    // send stop bit
    twi_stop;
    Serial.println("done dummy date. stop bit sent");
    
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
