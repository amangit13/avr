
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

void writeToOLED(uint8 data)
{
  twi_start;
  twi_wait;
  twi_setData(0x40);
  twi_senddata;
  twi_wait;
  twi_ret_on_nack;
  twi_setData(data);
  twi_senddata;
  twi_wait;
  twi_stop;
}

void sendCommand(uint8 command)
{
  Serial.println(command);
  twi_start;
  twi_wait;
  twi_setdata (0x3D);
  twi_senddata;
  twi_wait;
  twi_ret_on_nack
  
  Serial.println("ack recieved");
  
  twi_setdata (0); // control
  twi_senddata;
  twi_ret_on_nack;

  twi_setdata (command);
  twi_senddata;
  twi_wait;
  twi_stop;
  
}


void oled_begin()
{
  DDRC = 0xff;
  PINC = 0xff;
  
  Serial.println("oled begin");
  twi_start;
  twi_wait;
  twi_setdata (0x3D);
  twi_senddata;
  twi_ret_on_nack;
  Serial.println("slave ack");
  
  sendCommand(0xAE); // display off
  sendCommand(0xD5); // display clock div
  sendCommand (0x80); // ration 0x80

  sendCommand(0xA8); // set multiplex

  sendCommand(0xD3); // display offset
  sendCommand(0x0); // no offset
  sendCommand (0x40); // line #0
  sendCommand (0x8D);// charge pump
  sendCommand (0x10); // external VCC
  sendCommand (0x20); // memory mode
  sendCommand (0); // act like ks0108
  sendCommand (0xA0 | 0x1);// segremap
  sendCommand (0xC8);
  // 128 x 64
  sendCommand (0xDA); // compins;
  sendCommand (0x12);
  
  sendCommand (0x81); // set contrast
  sendCommand (0x9F); // external vcc

  sendCommand(0xD9); // set pre charge
  sendCommand(0x22); // external vcc

  sendCommand (0xD8); // set vcom detect
  sendCommand (0x40);
  sendCommand (0xA4); // Displayon_resume
  sendCommand (0xA6); // normal display

  sendCommand (0x2E); // deactivate scroll
  sendCommand (0xAF); // display on
 
}

void twisetup()
{
    Serial.println("start");
 
  // start bit
  twi_start;
  twi_wait;

  Serial.print("status ");   Serial.println(TWSR);
  
  // send address
  twi_setdata (0x3D); 
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
    twi_setdata (0); 
    twi_senddata;
    twi_wait;

    // send stop bit
    twi_stop;
    Serial.println("done dummy date. stop bit sent");
    
  }
}

void setup() {
  // put your setup code here, to run once:
  DDRC = 0xff;
  PINC = 0xff; // enable pullups
  Serial.begin(115200);
  
  // 400Khz. TWBR 12 for 400Khz, or 72 for 100Khz. leave TWSR as is for prescalar of 1. first two bits zero
  TWBR = 12;
  TWSR &= 0b11111100;

  oled_begin();
  Serial.println("done");

}

void loop() {
  // put your main code here, to run repeatedly:
  
}
