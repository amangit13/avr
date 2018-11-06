#define ALPHA
#define NUMBERS
#define LINES

#include "SSD1306.h"
#include "twi.h"
//#include "SerialDebug.h"
#include "chars.h"
void setup() {

  uint8_t x = 0;
  uint8_t cont = 0;
  int8_t stpcont = 1;
  
  twi_init;

  displayBegin();
  clearDisplay();
  displayPGMData(0,0,127,1,chars);
  displayPGMData(0,1,80,1,&chars[16*8]);
  displayPGMData(0,2,80,1,nums);
  displayPGMData(0,3,8*4,1,lines);
  
  while(1)
  {
    displayCommand (0x81); // set contrast
    displayCommand (cont); // external vcc
    cont+= stpcont;
    
    if (cont > 254)
      stpcont *= -1;
          
    displayPattern (64, 3, 50, 0xff, x);
    x++;
  }
}

void loop() {
  // put your main code here, to run repeatedly:cha

}
