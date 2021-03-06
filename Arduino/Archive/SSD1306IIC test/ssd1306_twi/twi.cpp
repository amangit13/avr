/*
  twi.c - TWI/I2C library for Wiring & Arduino
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 2012 by Todd Krein (todd@krein.org) to implement repeated starts
*/

#include <math.h>
#include <stdlib.h>
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "twiport.h"
#include <hardwareSerial.h>

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#include "twi.h"

static volatile uint8_t twi_state;
static volatile uint8_t twi_slarw;
static volatile uint8_t twi_sendStop;			// should the transaction end with a stop
static volatile uint8_t twi_inRepStart;			// in the middle of a repeated start

//static void (*twi_onSlaveTransmit)(void);
//static void (*twi_onSlaveReceive)(uint8_t*, int);

static uint8_t twi_masterBuffer[TWI_BUFFER_LENGTH]; // 9
static volatile uint8_t twi_masterBufferIndex;
static volatile uint8_t twi_masterBufferLength;

static volatile uint8_t twi_error;

static volatile uint8_t clearscreen;
/*
   Function twi_init
   Desc     readys twi pins and sets twi bitrate
   Input    none
   Output   none
*/
void twi_init(void)
{
  // initialize state
  twi_state = TWI_READY;
  twi_sendStop = true;		// default value
  twi_inRepStart = false;
  clearscreen = false;
  PORTC = 0xff;

  // initialize twi prescaler and bit rate
  cbi(TWSR, TWPS0);
  cbi(TWSR, TWPS1);

  // 400KHz. 6 = 571Khz. FPS with 129 mem is ~42 fps
  TWBR = 10; //((F_CPU / TWI_FREQ) - 16) / 2;

  /* twi bit rate formula from atmega128 manual pg 204
    SCL Frequency = CPU Clock Frequency / (16 + (2 * TWBR))
    note: TWBR should be 10 or higher for master mode
    It is 72 for a 16mhz Wiring board with 100kHz TWI */

  // enable twi module, acks, and twi interrupt
  TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA);
}

/*
   Function twi_disable
   Desc     disables twi pins
   Input    none
   Output   none
*/
void twi_disable(void)
{
  // disable twi module, acks, and twi interrupt
  TWCR &= ~(_BV(TWEN) | _BV(TWIE) | _BV(TWEA));

  // deactivate internal pullups for twi.
  //digitalWrite(SDA, 0);
  // digitalWrite(SCL, 0);
  PORTC = 0x0;
}


uint8_t twi_writeTo(uint8_t address, uint8_t* data, uint8_t length, uint8_t wait, uint8_t sendStop, uint8_t cls)
{
  uint8_t i;
  clearscreen = cls;

  // ensure data will fit into buffer
  if (TWI_BUFFER_LENGTH < length) {
    return 1;
  }

  // wait until twi is ready, become master transmitter
  while (TWI_READY != twi_state) {
    continue;
  }

  twi_state = TWI_MTX;
  twi_sendStop = sendStop;
  // reset error state (0xFF.. no error occured)
  twi_error = 0xFF;

  // initialize buffer iteration vars
  twi_masterBufferIndex = 0;
  twi_masterBufferLength = length;

  // copy data to twi buffer
  for (i = 0; i < length; ++i) {
    twi_masterBuffer[i] = data[i];
  }

  // build sla+w, slave device address + w bit
  twi_slarw = TW_WRITE;
  twi_slarw |= address << 1;

  if (cls)
    twi_masterBufferLength  = 129; // clear all screen

 
  // if we're in a repeated start, then we've already sent the START
  // in the ISR. Don't do it again.
  //
/*  if (true == twi_inRepStart)
  {
    // if we're in the repeated start state, then we've already sent the start,
    // (@@@ we hope), and the TWI statemachine is just waiting for the address byte.
    // We need to remove ourselves from the repeated start state before we enable interrupts,
    // since the ISR is ASYNC, and we could get confused if we hit the ISR before cleaning
    // up. Also, don't enable the START interrupt. There may be one pending from the
    // repeated start that we sent outselves, and that would really confuse things.
    twi_inRepStart = false;			// remember, we're dealing with an ASYNC ISR

    do
    {
      TWDR = twi_slarw;
    }
    while (TWCR & _BV(TWWC));


    TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE);	// enable INTs, but not START
  }
  else */
  {
    // send start condition
    TWCR = _BV(TWINT) | _BV(TWEA) | _BV(TWEN) | _BV(TWIE) | _BV(TWSTA);	// enable INTs
  }

  // wait for write operation to complete
  while (wait && (TWI_MTX == twi_state)) {
    continue;
  }

  if (twi_error == 0xFF)
    return 0;	// success
  else if (twi_error == TW_MT_SLA_NACK)
    return 2;	// error: address send, nack received
  else if (twi_error == TW_MT_DATA_NACK)
    return 3;	// error: data send, nack received
  else
    return 4;	// other twi error
}



void twi_reply(uint8_t ack)
{
  // transmit master read ready signal, with or without ack
  if (ack) {
    TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWINT) | _BV(TWEA);
  } else {
    TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWINT);
  }
}

/*
   Function twi_stop
   Desc     relinquishes bus master status
   Input    none
   Output   none
*/
void twi_stop(void)
{
  // send stop condition
  TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA) | _BV(TWINT) | _BV(TWSTO);

  // wait for stop condition to be exectued on bus
  // TWINT is not set after a stop condition!
  while (TWCR & _BV(TWSTO)) {
    continue;
  }

  // update twi state
  twi_state = TWI_READY;
}

/*
   Function twi_releaseBus
   Desc     releases bus control
   Input    none
   Output   none
*/
void twi_releaseBus(void)
{
  // release bus
  TWCR = _BV(TWEN) | _BV(TWIE) | _BV(TWEA) | _BV(TWINT);

  // update twi state
  twi_state = TWI_READY;
}

ISR(TWI_vect)
{
  switch (TW_STATUS) 
  {
    // All Master
    case TW_START:     // sent start condition
    case TW_REP_START: // sent repeated start condition
      // copy device address and r/w bit to output register and ack
      TWDR = twi_slarw;
      twi_reply(1);
      break;

    // Master Transmitter
    case TW_MT_SLA_ACK:  // slave receiver acked address
    case TW_MT_DATA_ACK: // slave receiver acked data

      // if there is data to send, send it, otherwise stop
      if (twi_masterBufferIndex < twi_masterBufferLength)
      {
        // copy data to output register and ack
        if (twi_masterBufferIndex == 0) // at index 0 send address or command
        {
          TWDR = twi_masterBuffer[0];
          twi_masterBufferIndex++;
        }
        else if (clearscreen)
        {
          TWDR = twi_masterBuffer[1]; // apply pattern at index 1. 0x00 to clear the screen.
          twi_masterBufferIndex++; // this will go to 1024 for full screen clear
        }
        else
        {
          TWDR = twi_masterBuffer[twi_masterBufferIndex++];
        }

        twi_reply(1);
      }
      else
      {
        if (twi_sendStop)
          twi_stop();
/*        else
        {
          twi_inRepStart = true;	// we're gonna send the START
          // don't enable the interrupt. We'll generate the start, but we
          // avoid handling the interrupt until we're in the next transaction,
          // at the point where we would normally issue the start.
          TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN) ;
          twi_state = TWI_READY;
        }*/
      }
      break;
    case TW_MT_SLA_NACK:  // address sent, nack received
      twi_error = TW_MT_SLA_NACK;
      twi_stop();
      break;
    case TW_MT_DATA_NACK: // data sent, nack received
      twi_error = TW_MT_DATA_NACK;
      twi_stop();
      break;
    case TW_MT_ARB_LOST: // lost bus arbitration
      twi_error = TW_MT_ARB_LOST;
      twi_releaseBus();
      break;

    // All
    case TW_NO_INFO:   // no state information
      break;
    case TW_BUS_ERROR: // bus error, illegal stop/start
      twi_error = TW_BUS_ERROR;
      twi_stop();
      break;
  }
}
