char data;

void setup() {
  Serial.begin(115200);


}

void loop() {
  if(Serial.available() > 0){
    data = Serial.read();
    if (data == 'b'){
      digitalWrite(13,HIGH);
      digitalWrite(11,LOW);
      Serial.write(13);
    } else if (data == 'g') {
      digitalWrite(11,HIGH);
      digitalWrite(13,LOW);
      Serial.write(11);
   }
  }
  delay(1000);


}
