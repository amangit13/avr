#include "twi.h"
#include "ssd1306twi.h"
//#define _TWI_DEBUG

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(115200);
  uint8_t i = 0;
  twi_init();
  displayInit();
  while (1)
  {
    i ++;
    for (uint8_t x = 0; x < 8; x++)
      displayData(0, x, i, 1);
  }

}


void loop() {
  // put your main code here, to run repeatedly:

}
