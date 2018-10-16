
//#include <Wire.h>
#define twi_wait  while (!(TWCR & (1<< TWINT))) 
#define twi_start   TWCR |= ((1<<TWEN) | (1<<TWSTA) | (1<<TWINT));

#define twi_stop     TWCR = ((1<<TWEN)|(1<<TWINT)|(1<<TWSTO))

#define twi_setdata(X) TWDR = X

#define twi_senddata   TWCR |= ((1<< TWEN) | (1<<TWINT))

#define twi_status (TWSR & 0xF8)
#define twi_nack 0x20
#define twi_ret_on_nack   if (twi_status == twi_nack)\
  {\
    twi_stop;\
    return;  \
  }

#define twi_masterWrite (X) twi_setdata (X) \
  twi_senddata; \

#define uint8 byte unsigned

void displayData(uint8 data)
{
  twi_start;
  twi_wait;

  twi_master_write (0x40);
  twi_wait;
  twi_ret_on_nack;
  
  twi_master_write(data);
  twi_wait;
  twi_stop;
}

void displayCommand(uint8 command)
{
  Serial.println(command);
  twi_start;
  twi_wait;
  
  twi_master_write(0x3D); // address
  twi_wait;
  twi_ret_on_nack;
  
  Serial.println("ack recieved");

  twi_master_write(0) // control
  twi_wait;
  twi_ret_on_nack;
  
  twi_master_write(command);
  twi_wait;
  twi_ret_on_nack;
}


void displayBegin()
{
  DDRC = 0xff;
  PINC = 0xff;
  
  Serial.println("oled begin");
  twi_start;
  twi_wait;

  twi_master_write (0x3D);
  twi_wait;
  twi_ret_on_nack;
  Serial.println("slave ack");
  
  displayCommand(0xAE); // display off
  displayCommand(0xD5); // display clock div
  displayCommand (0x80); // ration 0x80

  displayCommand(0xA8); // set multiplex

  displayCommand(0xD3); // display offset
  displayCommand(0x0); // no offset
  displayCommand (0x40); // line #0
  displayCommand (0x8D);// charge pump
  displayCommand (0x10); // external VCC
  displayCommand (0x20); // memory mode
  displayCommand (0); // act like ks0108
  displayCommand (0xA0 | 0x1);// segremap
  displayCommand (0xC8);
  // 128 x 64
  displayCommand (0xDA); // compins;
  displayCommand (0x12);
  
  displayCommand (0x81); // set contrast
  displayCommand (0x9F); // external vcc

  displayCommand(0xD9); // set pre charge
  displayCommand(0x22); // external vcc

  displayCommand (0xD8); // set vcom detect
  displayCommand (0x40);
  displayCommand (0xA4); // Displayon_resume
  displayCommand (0xA6); // normal display

  displayCommand (0x2E); // deactivate scroll
  displayCommand (0xAF); // display on
 
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

  displayBegin();
  Serial.println("done");

}

void loop() {
  // put your main code here, to run repeatedly:
  
}
