#include "DualVNH5019MotorShield.h"

DualVNH5019MotorShield md;

void setup() {
  Serial.begin(115200);
  md.init();
}

void loop() {
    if (Serial.available() > 0){
      switch((Serial.read() & ~0x20)){
        case 'P':
          md.setM1Brake(400);
          md.setM2Brake(400);
        break;
        case 'V':
          while(Serial.available() < 2);
          md.setM1Speed((Serial.read()-100)*4);
          md.setM2Speed((Serial.read()-100)*4);
        break;
      }
    }
}
