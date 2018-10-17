
#define twi_wait  while (!(TWCR & (1<< TWINT))) 
#define twi_start   TWCR |= ((1<<TWEN) | (1<<TWSTA) | (1<<TWINT));

#define twi_stop     TWCR = ((1<<TWEN)|(1<<TWINT)|(1<<TWSTO))

//#define twi_setdata(X) TWDR = X

#define twi_senddata(X)  TWDR = X <<1; TWCR |= ((1<< TWEN) | (1<<TWINT))

#define twi_status (TWSR & 0xF8)
#define twi_nack 0x20
#define twi_ret_on_nack   if (twi_status == twi_nack)\
  {\
    twi_stop;\
    return;  \
  }
#define uint8 byte unsigned


// write pixel data on oled
void displayData(uint8 data)
{

Serial.println("displaydata started");
  displayCommand(0x21); // set col address
  displayCommand(0); // col start
  displayCommand (127); // col end

  displayCommand(0x22); //set page address
  displayCommand(0);
  displayCommand(7); // page end address for 64 pixels

  twi_start;
  twi_wait;
  twi_senddata(0x3C); // send address
  twi_ret_on_nack;
  
  twi_senddata(0x40); // write data
  twi_wait;
  twi_ret_on_nack;
  
  twi_senddata(data); // send pixel data. Can be an array in the future. 
  twi_wait;
  twi_stop;
  
  Serial.println("displaydata end");
}

void displayCommand(uint8 command)
{
  Serial.print("command=");
  Serial.println(command);
  twi_start;
  twi_wait;
  
  twi_senddata(0x3C); // address
  twi_wait;
  twi_ret_on_nack;
  
  twi_senddata(0); // next byte is a command byte. co = 0 dc = 0
  twi_wait;
  twi_ret_on_nack;
  
  twi_senddata(command);
  twi_wait;
  twi_stop;

  Serial.println("command done");
}


void displayBegin()
{
  
  Serial.println("oled begin");
  
  displayCommand(0xAE); // display off
  displayCommand(0xD5); // display clock div
  displayCommand (0x80); // ration 0x80

  displayCommand(0xA8); // set multiplex
  displayCommand (63); // lcd height -1
  
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
  displayCommand (0xA4); // Displayon_resume*/
  displayCommand (0xA6); // invert display

  displayCommand (0x2E); // deactivate scroll
  displayCommand (0xAF); // display on
  Serial.println("display begin done");
 
}

void setup() {
  // put your setup code here, to run once:
  DDRC = 0xff;
  PINC = 0xff; // enable pullups
  Serial.begin(115200);
  
  // enable I2C
  TWCR |= 1<<TWEN;
  
  // 400Khz. TWBR 12 for 400Khz, or 72 for 100Khz. leave TWSR as is for prescalar of 1. first two bits zero
  TWBR = 72;
  TWSR &= 0b11111100;

  displayBegin();

  displayData(0xff);
  Serial.println("setup done");
 
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
