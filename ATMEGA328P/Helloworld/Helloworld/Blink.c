void blink()
{
	DDRB = 0xff;
		
	while (1)
	{
		PORTB = 0xff;
		_delay_ms(500);
		PORTB = 0;
		_delay_ms(500);
	}

}