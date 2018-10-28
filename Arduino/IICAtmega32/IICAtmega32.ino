#include "SSD1306.h"
#include "twi.h"



void setup() {
  // put your setup code here, to run once:

  uint8_t x = 0;
  twi_init;

  displayBegin();
  for (x = 0; x < 255; x++)
    displayData(0, 0, 1024, x, x);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
