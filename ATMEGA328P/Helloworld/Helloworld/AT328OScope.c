#ifndef _AT328_ADC_EXTERN_VECT
#error Must define _AT328_ADC_EXTERN_VECT to enable oscilliscope ISR
#endif
#ifndef _AT328_UART_EXTERN_VECT
#error Must define _AT328_UART_EXTERN_VECT to enable oscilliscope ISR
#endif

void Osc_init()
{
	AT328_ADC_init(1);
	AT328_UART_init();
}

ISR(ADC_vect)
{
	
}

ISR (USART_TX_vect)
{
	
}