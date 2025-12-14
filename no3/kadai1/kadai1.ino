int PIN[] = {9,10,11,12,13};
int PIN_COUNT = sizeof(PIN) / sizeof(PIN[0]);

void setup() {
  for (int i = 0; i < PIN_COUNT; i++) {
    pinMode(PIN[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < PIN_COUNT; i++) {
    digitalWrite(PIN[i], HIGH);
    delay(500);
    digitalWrite(PIN[i], LOW);
  }
}
