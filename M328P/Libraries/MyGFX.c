#include "SSD1306Compact.h"

// displaybegin will set the start address. subsequent call to plot will put pixel in the next Y axis in the same col
void plot(uint8_t x, uint8_t y)
{
	displaybegin(x, y/8);
	uint8_t bit = y%8;
	uint8_t byte = 1 << bit;
	fastSPIwrite(byte);
}

void clearcolumn(uint8_t x)
{
	for (uint8_t i =0; i<8; i++)
	{
		displaybegin(x,i);
		fastSPIwrite(0);
	}
	displayend();
	
}

void scroll()
{
	ssd1306_command(0x2E); // deactivtae scroll
	ssd1306_command(0x27);//SSD1306_LEFT_HORIZONTAL_SCROLL
	ssd1306_command(0X00); // dummy
	ssd1306_command(0); // page
	ssd1306_command(0Xff); // time interval
	ssd1306_command(6); //end page
	ssd1306_command(0x00);
	ssd1306_command(0Xff);
	ssd1306_command(0x2F); // activate scroll
}
