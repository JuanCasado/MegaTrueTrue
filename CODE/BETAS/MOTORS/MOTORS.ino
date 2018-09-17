#include <Wire.h>

#define INFO 'Z'
#define ADD 0x58
#define LED 13

#define MAX_BYTE 255

#define SPEED 0x01  //M1
#define TURN 0x00   //M2
//REGITERS FOR ENCODER 1
#define EN1A 0x02
#define EN1B 0x03
#define EN1C 0x04
#define EN1D 0x05
//REGITERS FOR ENCODER 1
#define EN2A 0x06
#define EN2B 0x07
#define EN2C 0x08
#define EN2D 0x09
//POWER
#define VOLTS 0x0A
#define AMPS1 0x0B
#define AMPS2 0x0C
#define SW 0x0D     //SW VERSION
#define ACCEL 0x0E  //SETS THE ACCEL RATE (5 default)
#define MODE 0x0F   //SETS THE MODE (0 default)
/* MODES
   0 -> 0 (Full Reverse) 128 (Stop) 255 (Full Forward)  INDEPENDENT MOTORS
   1 -> -128 (Full Reverse) 0 (Stop) 127 (Full Forward) INDEPENDENT MOTORS
   2 -> 0 (Full Reverse) 128 (Stop) 255 (Full Forward)  TURN MODE
   3 -> -128 (Full Reverse) 0 (Stop) 127 (Full Forward) TURN MODE
*/
#define COMAND 0x10 //ENABLES COMANDS
//COMANDS
#define RESET 0x20  //RESETS ENCODER REGITERS
#define ACCEL_OFF 0x30
#define ACCEL_ON 0x31
#define TIMEOUT_OFF 0x32
#define TIMEOUT_ON 0x33

#define MIN_CHAR -128
#define MAX_CHAR 127

#define VEL_MIN_EPROM 0
#define VEL_MAX_EPROM 10
#define P_ODOM_EPROM_D 20
#define I_ODOM_EPROM_D 30
#define P_ODOM_EPROM_I 40
#define I_ODOM_EPROM_I 50

#define RANGE 100
#define INICIO_INTEGRAL 50
byte vel_max = 100;
byte vel_min = 17;
float p_odom_d = 0;
float i_odom_d = 0;
float d_odom_d = 0;
float p_odom_i = 0;
float i_odom_i = 0;
float d_odom_i = 0;

#define AVANZAR_TARJETA 'A'
#define RETROCEDER_TARJETA 'R'
#define DERECHA_TARJETA 'D'
#define IZQUIERDA_TARJETA 'I'
#define GO_TARJETA 'G'
#define ERR_TARJETA 'E'

#define PIN           9
#define NUMPIXELS     16
#define D 0
#define I 1

int en_d = 0;
int en_i = 0;

void setup () {
  Wire.begin();
  Serial.begin(115200);

  iniciar ();
  reset_encoders ();
  parar ();

  Serial.println ("MEGA_TRUE_TRUE LISTO");
  Serial.println ("ELIJA MODO");
}
byte to_do = 0;
byte lectura = 0;
unsigned long tiempo_anterior = 0;
byte vel = 0;

void loop () {
#define AVANZAR 'A'
#define RETROCEDER 'R'
#define DERECHA 'D'
#define IZQUIERDA 'I'
#define AVANZAR_S '1'
#define RETROCEDER_S '2'
#define DERECHA_S '3'
#define IZQUIERDA_S '4'
#define VEL 'V'
  if (Serial.available()) {
    lectura = lectura_serial();
    if (lectura == VEL) {
      vel = read_number (true);
    } else
      to_do = lectura;
  }
  actualizar_encoders ();
  if ((millis() - tiempo_anterior) > 100) {
    tiempo_anterior = millis();
    switch (to_do) {
      case AVANZAR:
        mover_motor(D, vel);
        mover_motor(I, vel);
        break;
      case RETROCEDER:
        mover_motor(D, -vel);
        mover_motor(I, -vel);
        break;
      case DERECHA:
        mover_motor(D, -vel);
        mover_motor(I, vel);
        break;
      case IZQUIERDA:
        mover_motor(D, vel);
        mover_motor(I, -vel);
        break;
      case AVANZAR_S:

        break;
      case RETROCEDER_S:

        break;
      case DERECHA_S:

        break;
      case IZQUIERDA_S:

        break;
    }
    /*Serial.println("---");
    Serial.println(en_d);
    Serial.println(en_i);*/
    Wire.beginTransmission(ADD);
    Wire.write(EN1A);
    Wire.endTransmission();
    Wire.requestFrom(ADD, 1, true);
        Wire.read();
    Wire.beginTransmission(ADD);
    Wire.write(EN1B);
    Wire.endTransmission();
    Wire.requestFrom(ADD, 1, true);
        Wire.read();
    Wire.beginTransmission(ADD);
    Wire.write(EN1C);
    Wire.endTransmission();
    Wire.requestFrom(ADD, 1, true);
        Wire.read();
    Wire.beginTransmission(ADD);
    Wire.write(EN1D);
    Wire.endTransmission();
    Wire.requestFrom(ADD, 1, true);
    Serial.println(Wire.read());
  }
}




byte read_number (boolean manual)
{
  if (manual) {
    long data = 0;
    for (char x = 0; x < 3; x++) {
      data *= 10;
      while (Serial.available() < 1);
      data += (Serial.read() - '0');
    }
    return (char) constrain (data, 0, MAX_CHAR);
  }
  else {
    while (Serial.available() < 1);
    return constrain (Serial.read(), 0, MAX_CHAR);
  }
}
