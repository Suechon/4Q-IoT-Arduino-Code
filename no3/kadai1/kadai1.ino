const uint8_t firstPin = 9;
const uint8_t lastPin  = 13;

uint8_t currentPin = firstPin;

void setup() {
  for (uint8_t p = firstPin; p <= lastPin; p++) {
    pinMode(p, OUTPUT);
    digitalWrite(p, LOW);
  }
}

void loop() {
  uint8_t prevPin = currentPin;

  if (currentPin < lastPin) currentPin++;
  else currentPin = firstPin;

  digitalWrite(prevPin, LOW);
  digitalWrite(currentPin, HIGH);

  delay(500);
}
