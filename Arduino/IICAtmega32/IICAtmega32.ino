#include "SSD1306.h"
#include "twi.h"
//#include "SerialDebug.h"

void setup() {

  
  uint8_t x = 0;
  twi_init;

  displayBegin();
  while(1)
  {
    displayData(0, 0, 1024, 0xff, x);
    x++;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
