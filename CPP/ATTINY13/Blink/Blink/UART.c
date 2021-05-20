#define BAUD9600 250
#define BAUD19200 125
#define BAUD4800 500
#define DLY BAUD4800

void sbyte (int_fast8_t s)
{
	PORTB = 0x00; // start bit
	_delay_loop_2(DLY);
	int i = 0;
	while (i<8)
	{
		PORTB = 0xFE | s >> i;
		_delay_loop_2(DLY);
		i++;
	}
	// send end bit
	PORTB = 0xff;
	_delay_loop_2(DLY);
	
}
void swrite (const char *s)
{
	while (*s) sbyte(*s++);
}
