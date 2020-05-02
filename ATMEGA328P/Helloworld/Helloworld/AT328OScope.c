#ifndef _AT328_ADC_EXTERN_VECT
#error Must define _AT328_ADC_EXTERN_VECT to enable oscilliscope ISR
#endif

void AT328_OSC_init()
{
	AT328_UART_init();
	AT328_ADC_init(AT328_ADC_FREEFLOW);
}

void AT328_OSC_stop()
{
	AT328_ADC_RESET();
}

#ifdef _AT328_ADC_EXTERN_VECT
ISR(ADC_vect)
{
	AT328_UART_out(ADCH);
}
#endif