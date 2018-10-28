#include <avr/io.h>
#include <avr/interrupt.h>
static volatile uint8_t buffer[1024];

#define twi_init DDRC = 0XFF; PINC = 0XFF; PORTC = 0xFF; TWSR &= 0b11111100; TWBR = 4; TWCR = 0b01000100

#define twi_wait  while (!(TWCR & (1<< TWINT)))

//TWCR = TWINT TWEA TWSTA TWSTO TWWC TWEN --- TWIE
#define twi_start   TWCR = 0b11100100

//TWCR = TWINT TWEA TWSTA TWSTO TWWC TWEN --- TWIE
#define twi_stop TWCR = 0b11010100

#define twi_senddata(X)  TWDR = X; TWCR = 0b11000101

#define twi_sendaddr(X)  TWDR = 0; TWDR = X<<1; TWCR = 0b11000100

#define twi_status (TWSR & 0xF8)

#define twi_nack 0x20

#define twi_ret_on_nack   if (twi_status == twi_nack)\
  {\
    twi_stop;\
    return;  \
  }


ISR(TWI_vect)
{
  
}
