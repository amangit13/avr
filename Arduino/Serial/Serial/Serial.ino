void setup() {
  // put your setup code here, to run once:
  DDRD = 0xFF;
  PORTD = 0xFF;
}

void loop() {
  Serial.begin(9600);
  while (1)
  {
    Serial.write("Hello");
    delay(1000);
  }
}
