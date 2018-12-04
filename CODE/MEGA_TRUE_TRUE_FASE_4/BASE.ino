void base () {
#define MAX_DATA 50
#define AZUL_O 'O'
#define AZUL_C 'C'
#define RED 'R'
#define VER 'V'
#define AMAR 'A'
#define MOR 'M'
#define BLAN 'B'
#define S1 '1'
#define S2 '2'
#define S3 '3'
#define S4 '4'
#define S5 '5'
#define S6 '6'
#define S7 '7'
#define S8 '8'
#define S9 '9'
#define S10 '<'
#define S11 '>'
#define S12 '*'
#define VEL 'Z'
#define AVANZAR 'W'
#define RETROCEDER 'S'
#define DERECHA 'D'
#define IZQUIERDA 'I'
  uint32_t color_base = AZUL_OSCURO_;
  char vder = 0;
  char vizq = 0;
  bool go_done = false;
  bool iniciado = false;
  bool control_base = true;
  int datos = 0;
  int index = 0;
  char comandos [MAX_DATA];
  Serial.println("BASE");
  melodia(1);
  while (control_base) {
    while (iniciado) {
      if (index <= datos) {
        switch (comandos[index]) {
          case AVANZAR:
            mover (vel_max, vel_max);
            delay(5000);
            break;
          case RETROCEDER:
            mover (-vel_max, -vel_max);
            delay(5000);
            break;
          case DERECHA:
            mover (vel_max, -vel_max);
            delay(3000);
            break;
          case IZQUIERDA:
            mover (-vel_max, vel_max);
            delay(3000);
            break;
        }
        parar();
        delay(500);
        index ++;
      } else {
        iniciado = false;
        index = 0;
        datos = 0;
      }
    }
    if (Serial2.available()) {
      switch (lectura_wifi()) {
        case VEL:
          vder = constrain(lectura_wifi() - 100, -vel_max, vel_max);
          vizq = lectura_wifi() - 100;
          mover (vder + vizq, vder - vizq);
          break;
        case AZUL_O:
          color_base = AZUL_OSCURO_;
          melodia(2);
          Serial.println("AZUL OSCURO");
          break;
        case AZUL_C:
          color_base = AZUL_CLARO_;
          melodia(2);
          Serial.println("AZUL CLARO");
          break;
        case RED:
          color_base = ROJO_;
          melodia(2);
          Serial.println("ROJO");
          break;
        case VER:
          color_base = VERDE_;
          melodia(2);
          Serial.println("VERDE");
          break;
        case BLAN:
          color_base = BLANCO_;
          melodia(2);
          Serial.println("BLANCO");
          break;
        case AMAR:
          color_base = AMARILLO_;
          melodia(2);
          Serial.println("AMARILLO");
          break;
        case MOR:
          color_base = MORADO_;
          melodia(2);
          Serial.println("MORADO");
          break;
        case S1:
          melodia(1);
          Serial.println("S1");
          break;
        case S2:
          melodia(2);
          Serial.println("S2");
          break;
        case S3:
          melodia(3);
          Serial.println("S3");
          break;
        case S4:
          melodia(4);
          Serial.println("S4");
          break;
        case S5:
          melodia(5);
          Serial.println("S5");
          break;
        case S6:
          melodia(6);
          Serial.println("S6");
          break;
        case S7:
          melodia(7);
          Serial.println("S7");
          break;
        case S8:
          melodia(8);
          Serial.println("S8");
          break;
        case S9:
          melodia(9);
          Serial.println("S9");
          break;
        case S10:
          melodia(10);
          Serial.println("S10");
          break;
        case S11:
          melodia(11);
          Serial.println("S11");
          break;
        case S12:
          melodia(12);
          Serial.println("S12");
          break;
      }
    }
    if (go_done) {
      if (podemos_leer_tarjeta()) {
        switch (tarjeta()) {
          case GO_TARJETA:
            iniciado = true;
            go_done = false;
            mostrar_circulo (MORADO_);
            mostrar_circulo (AZUL_CLARO_);
            mostrar_circulo (MORADO_);
            Serial.println("GO");
            break;
          case AVANZAR_TARJETA:
            if (datos < MAX_DATA) {
              comandos [datos] = AVANZAR;
              datos ++;
            }
            break;
          case RETROCEDER_TARJETA:
            if (datos < MAX_DATA) {
              comandos [datos] = RETROCEDER;
              datos ++;
            }
            break;
          case DERECHA_TARJETA:
            if (datos < MAX_DATA) {
              comandos [datos] = DERECHA;
              datos ++;
            }
            break;
          case IZQUIERDA_TARJETA:
            if (datos < MAX_DATA) {
              comandos [datos] = IZQUIERDA;
              datos ++;
            }
            break;
        }
      }
    } else {
      go_done = (podemos_leer_tarjeta() && (tarjeta() == GO_TARJETA));
      if (go_done) {
        Serial.println("START");
      }
    }
    if (Serial.available()) {
      if (lectura_serial() == 'X') {
        control_base = false;
      }
    }
    mostrar_todos (color_base);
    if (d_parar()) {
      parar();
      Serial.println("STOP");
    }
  }
}
