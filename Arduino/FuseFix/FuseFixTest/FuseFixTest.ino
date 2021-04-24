#define  DATA    PORTD // PORTD = Arduino Digital pins 0-7
#define  DATAD   DDRD  // Data direction register for DATA port
#define  VCC     8
#define  RDY     12     // RDY/!BSY signal from target
#define  OE      11
#define  WR      10
#define  BS1     9
#define  XA0     13
#define  XA1     18    // Analog inputs 0-5 can be addressed as
#define  PAGEL   19    // digital outputs 14-19
#define  RST     14    // Output to level shifter for !RESET
#define  BS2     16
#define  XTAL1   17
#define  BUTTON  15    // Run button

void setup() {
  DATA = 0x00;  // Clear digital pins 0-7
  DATAD = 0xFF; // set digital pins 0-7 as outputs
  pinMode(VCC, OUTPUT);
  pinMode(RDY, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(WR, OUTPUT);
  pinMode(BS1, OUTPUT);
  pinMode(XA0, OUTPUT);
  pinMode(XA1, OUTPUT);
  pinMode(PAGEL, OUTPUT);
  pinMode(RST, OUTPUT);  // signal to level shifter for +12V !RESET
  pinMode(BS2, OUTPUT);
  pinMode(XTAL1, OUTPUT);
  pinMode(BUTTON, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(VCC, LOW);
digitalWrite(RDY, LOW);
digitalWrite(OE, LOW);
digitalWrite(WR, LOW);
digitalWrite(BS1, LOW);
digitalWrite(XA0, LOW);
digitalWrite(XA1, LOW);
digitalWrite(PAGEL, LOW);
digitalWrite(RST, HIGH);
digitalWrite(BS2, LOW);
digitalWrite(XTAL1, LOW);
digitalWrite(BUTTON, LOW);
DATA=0xFF;

while(1);
delayMicroseconds(30)

}
