#include <Wire.h>
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
#define BATT 12
#define MIN_VOLTS 104
#define TIME_BAT 10000

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

#define COMAND 0x10 //ENABLES COMANDS
//COMANDS
#define RESET 0x20  //RESETS ENCODER REGITERS
#define ACCEL_OFF 0x30
#define ACCEL_ON 0x31
#define TIMEOUT_OFF 0x32
#define TIMEOUT_ON 0x33

#define MIN_CHAR -128
#define MAX_CHAR 127

#define RANGE 10
#define INICIO_INTEGRAL 80
byte vel_max = 90;
byte vel_min = 59;

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

#define TRESHOLD_LDR 400
#define TRESHOLD_COLOR 10
#define VECES_LDR 3

#define TIME 30

#define VECES_COLOR 7
#define FASE 3
#define ROJO 0
#define VERDE 1
#define AZUL 2

#define AVANZAR 'A'
#define RETROCEDER 'R'
#define DERECHA 'D'
#define IZQUIERDA 'I'
#define GO 'G'
#define ERR 'E'

unsigned long color_d [FASE];
unsigned long color_i [FASE];
byte indice_d = 0;
byte indice_i = 0;
byte tarjeta = 0;
bool reading = true;

long en_d = 0;
long en_i = 0;
long colores = 0;
long rojo_i = 0;
long verde_d = 0;
long verde_i = 0;
long azul_d = 0;
long azul_i = 0;

unsigned long tiempo_anterior_ldr = 0;
unsigned long tiempo_anterior_color = 0;
unsigned long tiempo_anterior_bat = 0;
byte contador_color = 0;
byte fase = 0;

unsigned long lectura_ldr = 0;
byte contador_ldr = 0;

boolean hay_tarjeta = false;
boolean tarjeta_nueva = false;
boolean error = false;

byte volts = 0;

uint32_t color = AZUL_OSCURO_;
bool needCharge = false;
bool go_done = false;
bool can_move = false;
int index = 0;
int amount = 0;
byte to_do [50];

#define FORWARD 150
#define GIRO 157

#define WAZUL_OSCURO 'O'
#define WAZUL_CLARO 'C'
#define WROJO 'R'
#define WAMARILLO 'A'
#define WVERDE 'V'
#define WMORADO 'M'
#define WBLANCO 'B'
#define WS1 '1'
#define WS2 '2'
#define WS3 '3'
#define WS4 '4'
#define WS5 '5'
#define WS6 '6'
#define WS7 '7'
#define WS8 '8'
#define WS9 '9'
#define WS10 '<'
#define WS11 '>'
#define WS12 '*'
#define WV 'H'

void setup() {
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT_I, INPUT);
  pinMode(OUT_D, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BATT, INPUT);
  Wire.begin();
  pixels.begin();
  Serial.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);

  reset();
  iniciar ();
  parar ();
  reset_encoders ();

  mostrar_todos (color);
  delay (3000);
  melodia(1);
  delay (3000);
  melodia(2);
}
int fr = 0;
int tr = 0;
void loop() {
  actualizar_distancia ();
  if (Serial2.available() > 0) {
    switch (lectura_wifi()) {
      case WV:
        fr = lectura_wifi() - 100;
        tr = lectura_wifi() - 100;
        mover(fr + tr, fr - tr);
        break;
      case WAZUL_OSCURO:
        color = AZUL_OSCURO_;
        break;
      case WAZUL_CLARO:
        color = AZUL_CLARO_;
        break;
      case WAMARILLO:
        color = AMARILLO_;
        break;
      case WROJO:
        color = ROJO_;
        break;
      case WVERDE:
        color = VERDE_;
        break;
      case WMORADO:
        color = MORADO_;
        break;
      case WBLANCO:
        color = BLANCO_;
        break;
      case WS1:
        melodia(1);
        break;
      case WS2:
        melodia(2);
        break;
      case WS3:
        melodia(3);
        break;
      case WS4:
        melodia(4);
        break;
      case WS5:
        melodia(5);
        break;
      case WS6:
        melodia(6);
        break;
      case WS7:
        melodia(7);
        break;
      case WS8:
        melodia(8);
        break;
      case WS9:
        melodia(9);
        break;
      case WS10:
        melodia(10);
        break;
      case WS11:
        melodia(11);
        break;
      case WS12:
        melodia(12);
        break;
    }
  }
  if (can_move) {
    melodia (6);
    delay (2000);
    parar();
    for (; index < amount; index++) {
      melodia (7);
      Serial.print ("ACCION ");
      switch (to_do[index]) {
        case AVANZAR:
          Serial.println("AVANZAR");
          odom (FORWARD, 0);
          break;
        case RETROCEDER:
          Serial.println("RETROCEDER");
          odom (-FORWARD, 0);
          break;
        case DERECHA:
          Serial.println("DERECHA");
          odom (0, -GIRO);
          break;
        case IZQUIERDA:
          Serial.println("IZQUIERDA");
          odom (0, GIRO);
          break;
      }
      parar();
      delay(1000);
    }
    melodia (6);
    amount = 0;
    can_move = false;
    parar();
    delay(1000);
  } else {
    ldr_run();
    if (hay_tarjeta) {
      parar();
      if (reading) {
        color_run();
        mostrar_procesando ();
      } else {
        mostrar_listo ();
        tarjeta_nueva = true;
      }
    } else {
      reset();
      reading = true;
      if (tarjeta_nueva) {
        if (tarjeta == GO) {
          if (go_done) {
            can_move = true;
            index = 0;
            go_done = false;
          } else {
            go_done = true;
          }
          Serial.println("TARJETA GO");
          melodia (2);
          mostrar_todos (AZUL_CLARO_);
          delay (900);
          mostrar_todos (BLANCO_);
          delay (400);
          mostrar_todos (ROJO_);
          delay (900);
        } else {
          if (go_done) {
            switch (tarjeta) {
              case AVANZAR:
                Serial.println("TARJETA AVANZAR");
                melodia (2);
                mostrar_todos (VERDE_);
                delay (900);
                mostrar_todos (BLANCO_);
                delay (400);
                mostrar_todos (VERDE_);
                delay (900);
                to_do[amount] = tarjeta;
                amount++;
                break;
              case RETROCEDER:
                Serial.println("TARJETA RETROCEDER");
                melodia (2);
                mostrar_todos (AMARILLO_);
                delay (900);
                mostrar_todos (BLANCO_);
                delay (400);
                mostrar_todos (AMARILLO_);
                delay (900);
                to_do[amount] = tarjeta;
                amount++;
                break;
              case DERECHA:
                Serial.println("TARJETA DERECHA");
                melodia (2);
                mostrar_todos (ROJO_);
                delay (900);
                mostrar_todos (BLANCO_);
                delay (400);
                mostrar_todos (VERDE_);
                delay (900);
                to_do[amount] = tarjeta;
                amount++;
                break;
              case IZQUIERDA:
                Serial.println("TARJETA IZQUIERDA");
                melodia (2);
                mostrar_todos (VERDE_);
                delay (900);
                mostrar_todos (BLANCO_);
                delay (400);
                mostrar_todos (ROJO_);
                delay (900);
                to_do[amount] = tarjeta;
                amount++;
                break;
              default:
                Serial.println("ERROR TARJETA");
                melodia (3);
                mostrar_todos (ROJO_);
                delay (600);
                mostrar_todos (BLANCO_);
                delay (400);
                mostrar_todos (MORADO_);
                delay (600);
                break;
            }
          } else {
            Serial.println("ERROR TARJETA");
            melodia (3);
            mostrar_todos (ROJO_);
            delay (600);
            mostrar_todos (BLANCO_);
            delay (400);
            mostrar_todos (MORADO_);
            delay (600);
          }
        }
      }
      tarjeta_nueva = false;
      readVolts();
      if (volts < MIN_VOLTS) {
        parar ();
        while (plug ()) {
          melodia (8);
          readVolts();
          Serial.print("VOLTS = ");
          Serial.println(volts);
        }
        melodia (5);
        while (!charged()) {
          readVolts();
          Serial.print("VOLTS = ");
          Serial.println(volts);
        }
        melodia (1);
      } else {
        mostrar_todos (color);
      }
      if (tiempo_anterior_bat < (millis() - TIME_BAT)) {
        tiempo_anterior_bat = millis();
        readVolts();
        Serial.print("VOLTS = ");
        Serial.println(volts);
      }
    }
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

byte lectura_serial () {
  while (!Serial.available());
  return (Serial.read() & ~0x20);
}
byte lectura_wifi () {
  while (!Serial2.available());
  return (Serial2.read());
}

void melodia (byte number) {
  Wire.beginTransmission(SOUND);
  Wire.write(number);
  Wire.endTransmission();
}

bool plug () {
  bool result = true;
  for (int x = 0; x < 500; x++) {
    result &= digitalRead (BATT);
    mostrar_circulo_error ();
    delay (10);
  }
  return result;
}
bool charged () {
  bool result = true;
  for (int x = 0; x < 500; x++) {
    result &= digitalRead (BATT);
    mostrar_circulo_gradiente ();
    delay (10);
  }
  return result;
}
