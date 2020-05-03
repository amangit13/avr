/*
 *
 * Created: 10/3/2018 10:32:55 AM
 * Author : home
 */ 

#define _AT328_ADC_EXTERN_VECT
#define F_CPU 16000000
#define _AT328_ADC_FREEFLOW 1

#include <avr/io.h>
#include <util/delay.h>
#include "AT328UART.c"
#include "AT328ADC.c"
#include "AT328OScope.c"
#include "AT328LogicAnalyzer.c"
int main(void)
{
	AT328_OSC_init();
	AT328_Logic_init(311);
	while (1);			
}

