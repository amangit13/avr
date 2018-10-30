#include "SSD1306.h"
#include "twi.h"
//#include "SerialDebug.h"
uint8_t const test[] PROGMEM = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
void setup() {

  
  uint8_t x = 0;
  twi_init;

  displayBegin();
  displayData(0,0,1024,1,8);
  displayPGMData(0,0,7,1,test);
  
  while(1)
  {
    displayData(32, 2, 96, 0xff, x);
    x++;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
