void mover_motor (byte motor, int vel) {
  boolean hacer = false;
  byte reg;
  if (motor == D) {
    hacer = true;
    reg = SPEED;
  } else if (motor == I) {
    reg = TURN;
    hacer = true;
  }
  if (hacer) {
    if (vel > 0)
      vel = constrain (vel, vel_min, vel_max);
    else if (vel < 0)
      vel = constrain (vel, -vel_max, -vel_min);
    Wire.beginTransmission(ADD);
    Wire.write(reg);
    Wire.write (vel);
    Wire.endTransmission();
  }
}

void parar () {
  Wire.beginTransmission(ADD);
  Wire.write(SPEED);
  Wire.write(0);
  Wire.endTransmission();

  Wire.beginTransmission(ADD);
  Wire.write(TURN);
  Wire.write(0);
  Wire.endTransmission();
}

void reset_encoders () {
  delay (50);
  Wire.beginTransmission(ADD);
  Wire.write(COMAND);
  Wire.write(RESET);
  Wire.endTransmission();
  for (int x = 0; x < 100; x++) {
    actualizar_encoders();
    delay (1);
  }
  delay (50);
}

void iniciar () {
#define ERR_MAX 2
  byte timeout = 0;
  Wire.beginTransmission(ADD);
  Wire.write(ACCEL);
  Wire.write(255);
  Wire.endTransmission();

  Wire.beginTransmission(ADD);
  Wire.write(COMAND);
  Wire.write(ACCEL_OFF);
  Wire.endTransmission();

  Wire.beginTransmission(ADD);
  Wire.write(MODE);
  Wire.write(1);
  Wire.endTransmission();

  Wire.beginTransmission(ADD);
  Wire.write(ACCEL);
  Wire.endTransmission();
  Wire.requestFrom(ADD, 1, true);
  Serial.print("ACCEL: ");
  espera_disponible ();
  Serial.println(Wire.read());
  Wire.beginTransmission(ADD);
  Wire.write(MODE);
  Wire.endTransmission();
  Wire.requestFrom(ADD, 1, true);
  Serial.print("MODE: ");
  espera_disponible ();
  Serial.println(Wire.read());
  Wire.beginTransmission(ADD);
  Wire.write(VOLTS);
  Wire.endTransmission();
  Wire.requestFrom(ADD, 1, true);
  Serial.print("VOLTS: ");
  espera_disponible ();
  Serial.println(Wire.read());
}

void actualizar_encoders () {
#define TIME_MEDIDA 20
#define MAX_MEDIDAS 3
  static byte dato1C = 0;
  static byte dato1D = 0;
  static byte dato2C = 0;
  static byte dato2D = 0;
  static unsigned long tiempo_anterior = 0;
  static byte to_read = 0;
  boolean next = false;
  if ((millis() - tiempo_anterior) > TIME_MEDIDA) {
    tiempo_anterior = millis();
    switch (to_read) {
      case 0:
        next = pedir_medida(EN1C, &dato1C);
        break;
      case 1:
        next = pedir_medida(EN1D, &dato1D);
        if (next) {
          en_i = 0;
          en_i += dato1C;
          en_i = en_i << 8;
          en_i += dato1D;
        }
        break;
      case 2:
        next = pedir_medida(EN2C, &dato2C);
        break;
      case 3:
        next = pedir_medida(EN2D, &dato2D);
        if (next) {
          en_d = 0;
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

boolean pedir_medida(byte en, byte *to_save) {
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

