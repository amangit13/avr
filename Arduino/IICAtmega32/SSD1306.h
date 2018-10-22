#include<hardwareSerial.h>
#define h(x) Serial.println(x, HEX);
#define p(x) Serial.println(x);
#define s Serial.begin(115200);

void displayCommand(uint8_t);
void displayData(uint8_t,uint8_t,uint16_t, uint8_t, uint8_t);
void displayBegin();
