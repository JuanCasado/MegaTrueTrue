#include <Wire.h>
#define ADD 0x40
void setup() {
  Wire.begin(ADD);
  Wire.onReceive(receiveEvent);
  Serial.begin(115200);
}

void loop() {
}

//I2c
void receiveEvent(int howMany){
  while (Wire.available()){
    Serial.println(Wire.read());
  }
}
