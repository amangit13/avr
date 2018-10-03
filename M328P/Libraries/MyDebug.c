uint8_t _debugrow = 0;

void debugLoc()
{
	//_debugrow++;
	
	if (_debugrow == 6)
	{
		_debugrow = 0;
				
	}
	
}

void debugStr(char * str)
{
	displaybegin(0,_debugrow);
	writeString(str);
	displayend();
	
	debugLoc();
	
}

void debugNum(uint16_t num)
{
	displaybegin(32, _debugrow);
	writeNumber(num);
	displayend();

	debugLoc();	
}