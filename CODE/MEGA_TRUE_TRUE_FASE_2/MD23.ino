#define ESPERA 8
int dato1A = 0;
int dato1B = 0;
int dato1C = 0;
int dato1D = 0;
int dato2A = 0;
int dato2B = 0;
int dato2C = 0;
int dato2D = 0;
byte to_read = 0;

void mover_motor (byte der, byte izq) {
  byte reg;
    if (der > 0)
      der = constrain (der, vel_min, vel_max);
    else if (vel < 0)
      der = constrain (der, -vel_max, -vel_min);
    if (izq > 0)
      izq = constrain (izq, vel_min, vel_max);
    else if (vel < 0)
      izq = constrain (izq, -vel_max, -vel_min);
    Serial3.write('V');
    Serial3.write(der+100);
    Serial3.write(izq+100);
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
  Wire.beginTransmission(ADD);
  Wire.write(ACCEL);
  Wire.endTransmission();
  Wire.requestFrom(ADD, 1, true);
  espera_disponible ();
  byte accel = Wire.read();
  Serial.print("ACCEL: ");
  Serial.println(accel);
  delay (ESPERA);
  Wire.beginTransmission(ADD);
  Wire.write(MODE);
  Wire.endTransmission();
  Wire.requestFrom(ADD, 1, true);
  espera_disponible ();
  byte mode = Wire.read();
  Serial.print("MODE: ");
  Serial.println(mode);
  delay (ESPERA);
  Wire.beginTransmission(ADD);
  Wire.write(VOLTS);
  Wire.endTransmission();
  Wire.requestFrom(ADD, 1, true);
  espera_disponible ();
  volts = Wire.read();
  Serial.print("VOLTS: ");
  Serial.println(volts);
  delay (ESPERA);
}

void actualizar_encoders () {
#define TIME_MEDIDA 10
#define MAX_MEDIDAS 7
  static unsigned long tiempo_anterior = 0;
  boolean next = false;
  if ((millis() - tiempo_anterior) > TIME_MEDIDA) {
    tiempo_anterior = millis();
    switch (to_read) {
      case 0:
        next = pedir_medida(EN1A, &dato1A);
        break;
      case 1:
        next = pedir_medida(EN2A, &dato2A);
        break;
      case 2:
        next = pedir_medida(EN1B, &dato1B);
        break;
      case 3:
        next = pedir_medida(EN2B, &dato2B);
        break;
      case 4:
        next = pedir_medida(EN1C, &dato1C);
        break;
      case 5:
        next = pedir_medida(EN2C, &dato2C);
        break;
      case 6:
        next = pedir_medida(EN1D, &dato1D);
        if (next) {
          en_i = 0;
          en_i += dato1A;
          en_i = en_i << 8;
          en_i += dato1B;
          en_i = en_i << 8;
          en_i += dato1C;
          en_i = en_i << 8;
          en_i += dato1D;
        }
        break;
      case 7:
        next = pedir_medida(EN2D, &dato2D);
        if (next) {
          en_d = dato2A;
          en_d = en_d << 8;
          en_d += dato2B;
          en_d = en_d << 8;
          en_d += dato2C;
          en_d = en_d << 8;
          en_d += dato2D;
        }
        break;
    }
    if (next)
      to_read ++;
    if (to_read > MAX_MEDIDAS) {
      to_read = 0;
    }
  }
}

boolean pedir_medida(byte en, int *to_save) {
  Wire.beginTransmission(ADD);
  Wire.write(en);
  Wire.endTransmission();
  Wire.requestFrom(ADD, 1, true);
  if (espera_disponible ()) {
    *to_save = Wire.read();
    return true;
  }
  return false;
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
