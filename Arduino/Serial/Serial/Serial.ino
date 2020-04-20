void setup() {
  // put your setup code here, to run once:
  DDRD = 0xFF;
  PORTD = 0xFF;
}

void loop() {
  // put your main code here, to run repeatedly:
  while (1)
  {
    Serial.write(65);
    delay(1000);
  }
}
