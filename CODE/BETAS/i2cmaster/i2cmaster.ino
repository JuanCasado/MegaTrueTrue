#include <Wire.h>
#define ADD 0x40
char data = 0;
void setup() {
  Wire.begin();
  Serial.begin(115200);
}

void loop() {
  if (Serial.available()){
    data = Serial.read();
    Serial.print(data);
    Wire.beginTransmission(ADD);
    Wire.write(data);
    Wire.endTransmission();
  }
}
