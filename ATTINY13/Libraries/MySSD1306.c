#include "MySSD1306.h"
#include <avr/pgmspace.h>
#include <util/delay.h>

#define HPORT(X,pin) X |= 1 << pin
#define LPORT(X,pin) X &= ~(1<<pin)

#define _CSP PORTC
#define _DCP PORTC
#define _RSTP PORTC

#define _CS PORTC5
#define _DC PORTC4
#define _RST PORTC3

#define _CLKP PORTB
#define _MOSIP PORTB

#define _CLK PORTB5
#define _MOSI PORTB3


void displayinit(uint8_t vccstate) {

  // set pin directions
  DDRB = 0xFF;
  DDRC = 0xff;
  
_delay_ms(10);

  HPORT(_RSTP,_RST);
  // VDD (3.3V) goes high at start, lets just chill for a ms
  _delay_ms(100);
  LPORT(_RSTP, _RST);
	_delay_ms(100);
  HPORT(_RSTP, _RST);
  _delay_ms(100);
  // turn on VCC (9V?)

  // Init sequence
  ssd1306_command(SSD1306_DISPLAYOFF);                    // 0xAE
  ssd1306_command(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
  ssd1306_command(0x80);                                  // the suggested ratio 0x80

  ssd1306_command(SSD1306_SETMULTIPLEX);                  // 0xA8
  ssd1306_command(SSD1306_LCDHEIGHT - 1);

  ssd1306_command(SSD1306_SETDISPLAYOFFSET);              // 0xD3
  ssd1306_command(0x0);                                   // no offset
  ssd1306_command(SSD1306_SETSTARTLINE | 0x0);            // line #0
  ssd1306_command(SSD1306_CHARGEPUMP);                    // 0x8D
 if (vccstate == SSD1306_EXTERNALVCC)
 {
    ssd1306_command(0x10);
  }
  else
  {
    ssd1306_command(0x14);
  }

  ssd1306_command(SSD1306_MEMORYMODE);                    // 0x20
  ssd1306_command(0x00);                                  // 0x0 act like ks0108
  ssd1306_command(SSD1306_SEGREMAP | 0x1);
  ssd1306_command(SSD1306_COMSCANDEC);


  ssd1306_command(SSD1306_SETCOMPINS);                    // 0xDA
  ssd1306_command(0x12);
  ssd1306_command(SSD1306_SETCONTRAST);                   // 0x81
  if (vccstate == SSD1306_EXTERNALVCC)
  {
    ssd1306_command(0x9F);
  }
  else
  {
    ssd1306_command(0xCF);
  }


  ssd1306_command(SSD1306_SETPRECHARGE);                  // 0xd9
  if (vccstate == SSD1306_EXTERNALVCC)
  {
    ssd1306_command(0x22);
  }
  else
  {
    ssd1306_command(0xF1);
  }
  ssd1306_command(SSD1306_SETVCOMDETECT);                 // 0xDB
  ssd1306_command(0x40);
  ssd1306_command(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
  ssd1306_command(SSD1306_NORMALDISPLAY);                 // 0xA6

  ssd1306_command(SSD1306_DEACTIVATE_SCROLL);

  ssd1306_command(SSD1306_DISPLAYON);//--turn on oled panel
}

/*
void invertDisplay(uint8_t i) {
  if (i) {
    ssd1306_command(SSD1306_INVERTDISPLAY);
  } else {
    ssd1306_command(SSD1306_NORMALDISPLAY);
  }
}
*/
void ssd1306_command(uint8_t c) {
    // SPI
    HPORT(_CSP,_CS);
    LPORT(_DCP, _DC);
    LPORT(_CSP, _CS);
    //fastSPIwrite(c);
    HPORT(_CSP,_CS);
}

void displaybegin(uint8_t x, uint8_t row)
{
    ssd1306_command(SSD1306_COLUMNADDR);
    ssd1306_command(x);   // Column start address (0 = reset)
    ssd1306_command(SSD1306_LCDWIDTH - 1); // Column end address (127 = reset)

    ssd1306_command(SSD1306_PAGEADDR);
    ssd1306_command(row); // Page start address (0 = reset)
    ssd1306_command(7); // Page end address

    HPORT(_CSP,_CS);
    HPORT(_DCP, _DC);
    LPORT(_CSP, _CS);
}

void displayend()
{
	HPORT(_CSP, _CS);
}

void displayclear() {

	displaybegin(0,0);

    for (uint16_t i = 0; i < (SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT / 8); i++)
    {
      fastSPIwrite(0);
    }

	displayend();

}

void inline fastSPIwrite(uint8_t d) {

  for (uint8_t bit = 0x80; bit; bit >>= 1)
  {
    LPORT(_CLKP, _CLK);

    if (d & bit)
      HPORT(_MOSIP, _MOSI);
    else
      LPORT(_MOSIP, _MOSI);
    HPORT(_CLKP, _CLK);
  }

}

void displayscroll(uint8_t startrow, uint8_t endrow)
{
	ssd1306_command(0x2E); // deactivtae scroll
	ssd1306_command(0x27);//SSD1306_LEFT_HORIZONTAL_SCROLL
	ssd1306_command(0X00); // dummy
	ssd1306_command(startrow); // page
	ssd1306_command(128); // time interval
	ssd1306_command(endrow); //end page
	ssd1306_command(0);
	ssd1306_command(0Xff);
	ssd1306_command(0x2F); // activate scroll
}


