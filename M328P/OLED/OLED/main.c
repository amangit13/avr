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
	displayinit(2);
	displayclear();
	displaybegin(0,0);
	
	for (uint8_t i = 0;i<255; i++)
	{
		fastSPIwrite(255);
	}
	displayend();
    /* Replace with your application code */
    while (1) 
    {
    }
}

