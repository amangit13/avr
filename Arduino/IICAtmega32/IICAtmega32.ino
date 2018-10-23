#include "SSD1306.h"
#include "twi.h"



void setup() {
  // put your setup code here, to run once:

  uint8_t x = 0;
  long st,ed;
  s
  twi_init;

  displayBegin();
  st = millis();
  for (x = 0; x < 255; x++)
    displayData(0, 0, 1024, x, x);
  ed = millis();
  
  p(ed-st)
}

void loop() {
  // put your main code here, to run repeatedly:

}
