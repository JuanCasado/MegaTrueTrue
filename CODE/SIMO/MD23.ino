#define ESPERA 8
#define SOUND_D 8000
int dato1A = 0;
int dato1B = 0;
int dato1C = 0;
int dato1D = 0;
int dato2A = 0;
int dato2B = 0;
int dato2C = 0;
int dato2D = 0;
byte to_read = 0;
unsigned long sound_d = 0;

void mover (int der, int izq) {
  if ((der == 0) and (izq == 0)) {
    parar();
  } else {
    if ((d_parar() and (der > vel_min) and (izq > vel_min))) {
      if ((sound_d + SOUND_D) < millis()) {
        melodia(11);
        sound_d = millis();
      }
    }
    byte d = constrain (der, -100, 100);
    byte i = constrain (izq, -100, 100);
    if (d > 0 ) {
      if (d < vel_min )
        d = vel_min;
    }
    else {
      if (d > -vel_min)
        d = -vel_min;
    }
    if (i > 0 ) {
      if (i < vel_min )
        i = vel_min;
    } else {
      if (i > -vel_min )
        i = -vel_min;
    }
    Serial3.write('V');
    Serial3.write(d + 100);
    Serial3.write(i + 100);
  }
}


void parar () {
  Serial3.write('P');
}

long leerEncoder_i() {
  long dato = 0;
  Wire.beginTransmission(ADD);
  Wire.write(EN1A);
  Wire.endTransmission();
  Wire.requestFrom(ADD, 1, true);
  while (Wire.available() < 1);
  dato += Wire.read();
  dato = dato << 8;
  Wire.beginTransmission(ADD);
  Wire.write(EN1B);
  Wire.endTransmission();
  Wire.requestFrom(ADD, 1, true);
  while (Wire.available() < 1);
  dato += Wire.read();
  dato = dato << 8;
  Wire.beginTransmission(ADD);
  Wire.write(EN1C);
  Wire.endTransmission();
  Wire.requestFrom(ADD, 1, true);
  while (Wire.available() < 1);
  dato += Wire.read();
  dato = dato << 8;
  Wire.beginTransmission(ADD);
  Wire.write(EN1D);
  Wire.endTransmission();
  Wire.requestFrom(ADD, 1, true);
  while (Wire.available() < 1);
  dato += Wire.read();
  return dato;
}

long leerEncoder_d() {
  long dato = 0;
  Wire.beginTransmission(ADD);
  Wire.write(EN2A);
  Wire.endTransmission();
  Wire.requestFrom(ADD, 1, true);
  while (Wire.available() < 1);
  dato += Wire.read();
  dato = dato << 8;
  Wire.beginTransmission(ADD);
  Wire.write(EN2B);
  Wire.endTransmission();
  Wire.requestFrom(ADD, 1, true);
  while (Wire.available() < 1);
  dato += Wire.read();
  dato = dato << 8;
  Wire.beginTransmission(ADD);
  Wire.write(EN2C);
  Wire.endTransmission();
  Wire.requestFrom(ADD, 1, true);
  while (Wire.available() < 1);
  dato += Wire.read();
  dato = dato << 8;
  Wire.beginTransmission(ADD);
  Wire.write(EN2D);
  Wire.endTransmission();
  Wire.requestFrom(ADD, 1, true);
  while (Wire.available() < 1);
  dato += Wire.read();
  return dato;
}

void reset_encoders () {
  delay (50);
  Wire.beginTransmission(ADD);
  Wire.write(COMAND);
  Wire.write(RESET);
  Wire.endTransmission();
  dato1A = 0;
  dato1B = 0;
  dato1C = 0;
  dato1D = 0;
  dato2A = 0;
  dato2B = 0;
  dato2C = 0;
  dato2D = 0;
  to_read = 0;
  delay (50);
}

void iniciar () {
  Wire.beginTransmission(ADD);
  Wire.write(ACCEL);
  Wire.write(255);
  Wire.endTransmission();
  delay (ESPERA);
  Wire.beginTransmission(ADD);
  Wire.write(COMAND);
  Wire.write(ACCEL_OFF);
  Wire.endTransmission();
  delay (ESPERA);
  Wire.beginTransmission(ADD);
  Wire.write(MODE);
  Wire.write(1);
  Wire.endTransmission();
  delay (ESPERA);
  readVolts();
  delay (ESPERA);
}

void readVolts() {
  delay (ESPERA);
  Wire.beginTransmission(ADD);
  Wire.write(VOLTS);
  Wire.endTransmission();
  Wire.requestFrom(ADD, 1, true);
  espera_disponible ();
  volts = Wire.read();
}

boolean espera_disponible () {
#define TIMES_ERR 2
  byte timeout = 0;
  while (Wire.available() < 1) {
    delay (1);
    if (timeout > TIMES_ERR) {
      return false;
    } else
      timeout ++;
  }
  return true;
}
