#ifndef _AVR_TWI_H_
#define _AVR_TWI_H_ 1


/* TWSR values (not bits) */
/* Master */
#define TW_START    0x08
#define TW_REP_START    0x10
/* Master Transmitter */
#define TW_MT_SLA_ACK   0x18
#define TW_MT_SLA_NACK    0x20
#define TW_MT_DATA_ACK    0x28
#define TW_MT_DATA_NACK   0x30
#define TW_MT_ARB_LOST    0x38

// Misc 
#define TW_NO_INFO    0xF8
#define TW_BUS_ERROR    0x00

/*
 * The lower 3 bits of TWSR are reserved on the ATmega163.
 * The 2 LSB carry the prescaler bits on the newer ATmegas.
 */
#define TW_STATUS_MASK    (_BV(TWS7)|_BV(TWS6)|_BV(TWS5)|_BV(TWS4)|\
        _BV(TWS3))
#define TW_STATUS   (TWSR & TW_STATUS_MASK)

/*
 * R/~W bit in SLA+R/W address field.
 */
#define TW_READ   1
#define TW_WRITE  0

#endif  /* _AVR_TWI_H_ */
