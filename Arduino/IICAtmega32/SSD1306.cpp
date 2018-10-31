#include "twi.h"
#include "SSD1306.h"
//#include "SerialDebug.h"
#include <avr/pgmspace.h>

void _beginData(uint8_t x, uint8_t row, uint8_t endx, uint8_t endrow)
{
  displayCommand(0x21); // set col address
  displayCommand(x); // col start
  displayCommand (endx); // col end

  displayCommand(0x22); //set page address
  displayCommand(row);
  displayCommand(endrow); // page end address for 64 pixels

  twi_start;
  twi_wait;

  twi_sendaddr(0x3C); // send address
  twi_wait;
  twi_ret_on_nack;

  twi_senddata(0x40); // write data
  twi_wait;


}

void displayCommand(uint8_t command)
{

  twi_start;
  twi_wait;

  twi_sendaddr(0x3C); // address
  twi_wait;

  twi_ret_on_nack;

  twi_senddata(0); // next byte is a command byte. co = 0 dc = 0
  twi_wait;

  twi_ret_on_nack;

  twi_senddata(command);
  twi_wait;

  twi_stop;
}

// write pixel data on oled
void displayPattern(uint8_t x, uint8_t row, uint16_t len, uint8_t ypattern, uint8_t xpattern)
{

  _beginData(x, row, 127, 7);
  twi_ret_on_nack;

  uint8_t mod = 0;

  for (uint16_t i = 0; i < len; i++)
  {
    mod = 0X01 & (xpattern >> i % 8);

    if (mod)
    {
      twi_senddata(ypattern); // send pixel data. Can be an array in the future.
    }
    else
    {
      twi_senddata(0); // send pixel data. Can be an array in the future.
    }

    twi_wait;
    twi_ret_on_nack;
  }

  twi_stop;
}

void displayPGMData(uint8_t x, uint8_t row, uint8_t width, uint8_t height, uint8_t *adr)
{
  uint16_t len = width * height;
  _beginData(x, row, x + width, row + height);
  for (uint16_t i = 0; i < len; i++)
  {
    twi_senddata(pgm_read_byte(adr + i));
    twi_wait;
    twi_ret_on_nack;
  }

  twi_stop;
}

void clearDisplay()
{
  displayPattern (0, 0, 1024, 0, 0);
}
void displayBegin()
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
  displayCommand (0x14); // external VCC
  displayCommand (0x20); // memory mode
  displayCommand (0); // act like ks0108
  displayCommand (0xA0 | 0x1);// segremap
  displayCommand (0xC8);
  // 128 x 64
  displayCommand (0xDA); // compins;
  displayCommand (0x12);

  displayCommand (0x81); // set contrast
  displayCommand (0xCF); // external vcc

  displayCommand(0xD9); // set pre charge
  displayCommand(0xF1); // external vcc

  displayCommand (0xD8); // set vcom detect
  displayCommand (0x40);
  displayCommand (0xA4); // Displayon_resume

  displayCommand (0x2E); // deactivate scroll
  displayCommand (0xAF); // display on

}
