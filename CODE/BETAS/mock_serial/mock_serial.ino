void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.write('M');
  Serial.write('M');
  Serial.write('S');
  Serial.write(2);
  Serial.write('U');
  Serial.write('D');
  Serial.write('P');
  Serial.write(70);
  Serial.write('F');
  Serial.write('X');
  delay(50000);
}
