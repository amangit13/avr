/*
 * OLED.c
 *
 * Created: 10/3/2018 4:25:30 PM
 * Author : home
 */ 
#define F_CPU 16000000

#include <avr/io.h>
#include "MySSD1306.c"

int main(void)
{
	displayinit(SSD1306_SWITCHCAPVCC);
	displayclear();
	displaybegin(0,1);
	fastSPIwrite(255);
	displayend();
    /* Replace with your application code */
    while (1) 
    {
    }
}

