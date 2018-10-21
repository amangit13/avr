#include <inttypes.h>
#include "ssd1306twi.h"
#include "twi.h"
static uint8_t data[9];

void displayCommand(uint8_t command)
{
  data[0] = 0;
  data[1] = command;

#ifdef _TWI_DEBUG
  {
    Serial.print("-- Buf Len ");
    Serial.println(2);

    for (uint8_t x = 0; x < 2; x++)
    {
      Serial.println(data[x], HEX);
    }
    Serial.println("--Buf End --");
  }
#endif

  twi_writeTo(0x3C, data, 2, 1, 1, 0);
}


void displayData(uint8_t x, uint8_t page, uint8_t pattern, uint8_t cls)
{
  displayCommand(0x21); // set col address
  displayCommand(x); // col start
  displayCommand (127); // col end

  displayCommand(0x22); //set page address
  displayCommand(page);
  displayCommand(7); // page end address for 64 pixels


  for (uint8_t x = 0; x < 9; x++)
  {
    data[x] = pattern;
  }

  data[0] = 0x40;

  for (int i = 0; i < 1; i++)
  {
#ifdef _TWI_DEBUG
    {
      Serial.print("-- Buf Len ");
      Serial.println(17);

      for (uint8_t x = 0; x < 17; x++)
      {
        Serial.println(data[x], HEX);
      }
      Serial.println("--Buf End --");
    }
#endif

    twi_writeTo(0x3C, data, 9, 1, 1, cls);
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
  displayCommand (0xA4); // Displayon_resume*/
  displayCommand (0xA6); // normal display

  displayCommand (0x2E); // deactivate scroll
  displayCommand (0xAF); // display on
}
