#include <Wire.h>
#include <EEPROM.h>
#include <Adafruit_NeoPixel.h>

#define SOUND 0x40

#define INFO 'Z'
#define ADD 0x58
#define LED 13
#define OUT_D 7
#define OUT_I 8
#define S2 5
#define S3 6
#define LDR_1 0
#define LDR_2 1

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
#define INICIO_INTEGRAL 80
byte vel_max = 0;
byte vel_min = 0;
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
#define NUMPIXELS     32
#define D 0
#define I 1
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
uint32_t ROJO_ = pixels.Color(255, 0, 0);
uint32_t VERDE_ = pixels.Color(0, 255, 0);
uint32_t AZUL_OSCURO_ = pixels.Color(0, 0, 255);
uint32_t BLANCO_ = pixels.Color(255, 255, 255);
uint32_t AMARILLO_ = pixels.Color(255, 255, 0);
uint32_t MORADO_ = pixels.Color(255, 0, 255);
uint32_t AZUL_CLARO_ = pixels.Color(0, 0, 255);
uint32_t APAGADO_ = pixels.Color(0, 0, 0);

long en_d = 0;
long en_i = 0;

byte volts = 0;

void setup() {
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT_I, INPUT);
  pinMode(OUT_D, INPUT);
  pinMode(LED, OUTPUT);
  Wire.begin();
  pixels.begin();
  Serial.begin(115200);
  Serial2.begin(115200);

  reset_tarjetas();

  set_vel_max ();
  set_vel_min ();
  set_p_odom_d ();
  set_i_odom_d ();
  set_p_odom_i ();
  set_i_odom_i ();
  
  iniciar ();
  sendConfig ();
  
  parar ();
  reset_encoders ();
  d_odom_i = 0;
  d_odom_i = 0;

  delay (3000);
  melodia(1);
  delay (3000);
  menuPrincipal();
}

boolean error = false;
void loop() {
#define ODOMETRIA 'O'
#define CONFIGURACION_MANUAL 'M'
#define CONFIGURACION 'C'
#define LIBERTAD 'L'
  if (Serial.available() > 0)
  {
    switch (lectura_serial ())
    {
      case ODOMETRIA:
        control_odometrico(false);
        break;
      case CONFIGURACION:
        configuracion(false);
        break;
      case CONFIGURACION_MANUAL:
        configuracion(true);
        break;
      case LIBERTAD:
        libertad();
        break;
      case INFO:
        menuPrincipal ();
        break;
      default:
        Serial.println ("COMANDO NO VALIDO 1");
        break;
    }
  }
  if (Serial2.available() > 0){
    switch (lectura_wifi ())
    {
      case ODOMETRIA:
        control_odometrico(false);
        break;
      case CONFIGURACION:
        configuracion(false);
        break;
      case CONFIGURACION_MANUAL:
        configuracion(true);
        break;
      case LIBERTAD:
        libertad();
        break;
      case INFO:
        menuPrincipal ();
        break;
      default:
        Serial.println ("COMANDO NO VALIDO 2");
        break;
    }
  }
  if (podemos_leer_tarjeta() && (tarjeta() == GO_TARJETA)) {
    control_odometrico(true);
  }
}

char read_number (boolean manual)
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

byte lectura_serial (){
  while(!Serial.available());
  return (Serial.read() & ~0x20);
}
byte lectura_wifi (){
  while(!Serial2.available());
  return (Serial2.read() & ~0x20);
}

void melodia (byte number){
  Wire.beginTransmission(SOUND);
  Wire.write(number);
  Wire.endTransmission();
}
