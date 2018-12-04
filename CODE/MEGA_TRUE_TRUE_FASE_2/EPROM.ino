void configuracion (boolean manual) {
#define VELOCIDAD_MAX 'A'
#define VELOCIDAD_MIN 'B'
#define P_ODOM_D 'C'
#define I_ODOM_D 'D'
#define P_ODOM_I 'E'
#define I_ODOM_I 'G'
#define SAVE 'S'
#define SALIR 'X'
  menuConfiguracion();
  boolean control = true;
  while (control) {
    if (Serial.available() > 0) {
      switch (Serial.read() & ~0x20) {
        case VELOCIDAD_MAX:
          vel_max = read_number(manual);
          Serial.print("VEL_MAX = ");
          Serial.println(vel_max);
          break;
        case VELOCIDAD_MIN:
          vel_min = read_number(manual);
          Serial.print("VEL_MIN = ");
          Serial.println(vel_min);
          break;
        case P_ODOM_D:
          p_odom_d = (float)read_number(manual) / 100;
          Serial.print("P_ODOM_D = ");
          Serial.println((byte)(p_odom_d * RANGE));
          break;
        case I_ODOM_D:
          i_odom_d = (float)read_number(manual) / 100;
          Serial.print("I_ODOM_D = ");
          Serial.println((byte)(i_odom_d * RANGE));
          break;
        case P_ODOM_I:
          p_odom_i = (float)read_number(manual) / 100;
          Serial.print("P_ODOM_I = ");
          Serial.println((byte)(p_odom_i * RANGE));
          break;
        case I_ODOM_I:
          i_odom_i = (float)read_number(manual) / 100;
          Serial.print("I_ODOM_I = ");
          Serial.println((byte)(i_odom_i * RANGE));
          break;
        case SAVE:
          EEPROM.update(VEL_MIN_EPROM, vel_min);
          set_vel_min ();
          EEPROM.update(VEL_MAX_EPROM, vel_max);
          set_vel_max ();
          EEPROM.update(P_ODOM_EPROM_D, (byte)(p_odom_d * RANGE));
          set_p_odom_d ();
          EEPROM.update(I_ODOM_EPROM_D, (byte)(i_odom_d * RANGE));
          set_i_odom_d ();
          EEPROM.update(P_ODOM_EPROM_I, (byte)(p_odom_i * RANGE));
          set_p_odom_i ();
          EEPROM.update(I_ODOM_EPROM_I, (byte)(i_odom_i * RANGE));
          set_i_odom_i ();
          melodia(7);
          break;
        case INFO:
          Serial.println("SALIR 'X'");
          Serial.println("VELOCIDAD_MAX 'A'");
          Serial.println(vel_max);
          Serial.println("VELOCIDAD_MIN 'B'");
          Serial.println(vel_min);
          Serial.println("P_ODOM_D 'C'");
          Serial.println(p_odom_d);
          Serial.println("I_ODOM_D 'D'");
          Serial.println(i_odom_d);
          Serial.println("P_ODOM_I 'E'");
          Serial.println(p_odom_i);
          Serial.println("I_ODOM_I 'G'");
          Serial.println(i_odom_i);
          Serial.println("SAVE 'S'");
          iniciar ();
          reset_encoders ();
          Serial2.write('M');
          Serial2.write('C');
          break;
        case SALIR:
          control = false;
          Serial.println ("ELIJA MODO:");
          break;
      }
      sendConfig ();
    }
  }
}

void set_vel_max () {
  vel_max = EEPROM.read(VEL_MAX_EPROM);
  Serial.print("VEL MAX = ");
  Serial.println(vel_max);
}

void set_vel_min () {
  vel_min = EEPROM.read(VEL_MIN_EPROM);
  Serial.print("VEL MIN = ");
  Serial.println(vel_min);
}

void set_p_odom_d () {
  p_odom_d = (float)EEPROM.read(P_ODOM_EPROM_D) / RANGE;
  Serial.print("P_ODOM_D = ");
  Serial.println((byte)(p_odom_d * RANGE));
}

void set_i_odom_d () {
  i_odom_d = (float)EEPROM.read(I_ODOM_EPROM_D) / RANGE;
  Serial.print("I_ODOM_D = ");
  Serial.println((byte)(i_odom_d * RANGE));
}

void set_p_odom_i () {
  p_odom_i = (float)EEPROM.read(P_ODOM_EPROM_I) / RANGE;
  Serial.print("P_ODOM_I = ");
  Serial.println((byte)(p_odom_i * RANGE));
}

void set_i_odom_i () {
  i_odom_i = (float)EEPROM.read(I_ODOM_EPROM_I) / RANGE;
  Serial.print("I_ODOM_I = ");
  Serial.println((byte)(i_odom_i * RANGE));
}

void sendConfig () {
  Serial2.write('C');
  Serial2.write(volts);
  Serial2.write((byte)(p_odom_d * RANGE));
  Serial2.write((byte)(i_odom_d * RANGE));
  Serial2.write((byte)(p_odom_i * RANGE));
  Serial2.write((byte)(i_odom_i * RANGE));
}
