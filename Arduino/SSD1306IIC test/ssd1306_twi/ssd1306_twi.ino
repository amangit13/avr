#include "twi.h"
byte unsigned data[16];

void displayCommand(byte unsigned command)
{
  data[0] = 0;
  data[1] = command;  
  twi_writeTo(0x3C,data, 2, 1, 1);
  
}

void displayData()
{
  displayCommand(0x21); // set col address
  displayCommand(0); // col start
  displayCommand (127); // col end

  displayCommand(0x22); //set page address
  displayCommand(0);
  displayCommand(7); // page end address for 64 pixels

  for (int i =0; i<64; i++)
  {
    data[0] = 0x40;
    twi_writeTo(0x3C, data, 16,1,1);
  }
}


void displayInit()
{
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
}

void setup() {
  // put your setup code here, to run once:
  twi_init();
  displayInit();
  displayData(); 
}

void loop() {
  // put your main code here, to run repeatedly:

}
