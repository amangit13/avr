#include "twi.h"
#include "ssd1306twi.h"
//#define _TWI_DEBUG

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  twi_init();
  displayInit();

  while (1)
    for (uint8_t x = 0; x < 255; x++)
      displayData(8,2,x);

}


void loop() {
  // put your main code here, to run repeatedly:

}
