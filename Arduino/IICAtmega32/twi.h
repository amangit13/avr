#include <avr/io.h>

#define twi_init DDRC = 0XFF; PINC = 0XFF; PORTC = 0xFF; TWCR = 1<<TWEN | 1<<TWEA; TWSR &= 0b11111100; TWBR = 10

#define twi_wait  while (!(TWCR & (1<< TWINT))) 

#define twi_start   TWCR = ((1<<TWEN) | (1<<TWSTA) | (1<<TWINT) | (1<<TWEA)); // missing  TWIE, 
//    TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE) | _BV(TWSTA);  // enable INTs

#define twi_stop TWCR = ((1<<TWEN)|(1<<TWINT)|(1<<TWSTO) | (1<<TWEA)) 
//  TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTO);

//#define twi_setdata(X) TWDR = X

#define twi_senddata(X)  TWDR = X; TWCR = ((1<< TWEN) | (1<<TWINT) | (1<<TWEA)) // missing  TWIE
#define twi_sendaddr(X)  TWDR = 0; TWDR = X<<1; TWCR = ((1<< TWEN) | (1<<TWINT) | (1<<TWEA)) // missing  TWIE
//    TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWINT) | _BV(TWEA);

#define twi_status (TWSR & 0xF8)

#define twi_nack 0x20

#define twi_ret_on_nack   if (twi_status == twi_nack)\
  {\
    twi_stop;\
    return;  \
  }
