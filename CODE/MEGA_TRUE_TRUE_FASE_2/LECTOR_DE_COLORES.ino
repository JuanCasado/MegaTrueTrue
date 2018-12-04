#define AVANZAR_TARJETA 'A'
#define RETROCEDER_TARJETA 'R'
#define DERECHA_TARJETA 'D'
#define IZQUIERDA_TARJETA 'I'
#define GO_TARJETA 'G'
#define ERR_TARJETA 'E'
#define FASE 3
#define ROJO 0
#define VERDE 1
#define AZUL 2

unsigned long color_d [FASE];
unsigned long color_i [FASE];
byte tarj = 0;
boolean podemos_leer_tarj = false;

byte tarjeta () {
  podemos_leer_tarj = false;
  mostrar_todos (APAGADO_);
  delay (500);
  Serial.print("TARJETA: ");
  switch (tarj) {
    case AVANZAR_TARJETA:
      Serial.println("AVANZAR");
      mostrar_todos (VERDE_);
      delay (700);
      mostrar_todos (APAGADO_);
      delay (200);
      mostrar_todos (VERDE_);
      delay (700);
      break;
    case RETROCEDER_TARJETA:
      Serial.println("RETROCEDER");
      mostrar_todos (AMARILLO_);
      delay (700);
      mostrar_todos (APAGADO_);
      delay (200);
      mostrar_todos (AMARILLO_);
      delay (700);
      break;
    case DERECHA_TARJETA:
      Serial.println("DERECHA");
      mostrar_todos (ROJO_);
      delay (700);
      mostrar_todos (APAGADO_);
      delay (200);
      mostrar_todos (VERDE_);
      delay (700);
      break;
    case IZQUIERDA_TARJETA:
      Serial.println("IZQUIERDA");
      mostrar_todos (VERDE_);
      delay (700);
      mostrar_todos (APAGADO_);
      delay (200);
      mostrar_todos (ROJO_);
      delay (700);
      break;
    case GO_TARJETA:
      Serial.println("GO");
      mostrar_todos (BLANCO_);
      delay (700);
      mostrar_todos (APAGADO_);
      delay (200);
      mostrar_todos (ROJO_);
      delay (700);
      break;
    case ERR_TARJETA:
      Serial.println("ERR");
      mostrar_todos (ROJO_);
      delay (700);
      mostrar_todos (MORADO_);
      delay (500);
      mostrar_todos (ROJO_);
      delay (700);
      break;
  }
  mostrar_todos (APAGADO_);
  delay (500);
  return tarj;
}
void rojo () {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  delay(5);
}
void azul () {
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  delay(5);
}
void verde () {
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  delay(5);
}
void blanco () {
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);
  delay(5);
}
byte leer_color (byte lado) {
  if (lado == D)
    return (byte)(MAX_BYTE - constrain(pulseIn(OUT_D, LOW), 0, MAX_BYTE));
  else if (lado == I)
    return (byte)(MAX_BYTE - constrain(pulseIn(OUT_I, LOW), 0, MAX_BYTE));
  else
    return 0;
}

void calcular () {
#define TRESHOLD_COLOR 10
  byte indice_d = 0;
  byte indice_i = 0;
  byte der = 0;
  byte izq = 0;
  boolean negro_d = true;
  boolean negro_i = true;

  for (int x = 0; x < (FASE - 1); x++) {
    negro_d = negro_d && (color_d[x] < TRESHOLD_COLOR);
    negro_i = negro_i && (color_i[x] < TRESHOLD_COLOR);
    if (color_d[x] > der) {
      der = color_d[x];
      indice_d = x;
    }
    if (color_i[x] > izq) {
      izq = color_i[x];
      indice_i = x;
    }
  }

  if (negro_i && indice_d == ROJO) {
    tarj = GO_TARJETA;
    melodia(4);
  } else if (negro_i || negro_d) {
    tarj = ERR_TARJETA;
    melodia(3);
  } else if ( indice_i == ROJO && indice_d == ROJO) {
    tarj = RETROCEDER_TARJETA;
    melodia(4);
  } else if ( indice_i == VERDE && indice_d == ROJO) {
    tarj = IZQUIERDA_TARJETA;
    melodia(4);
  } else if ( indice_i == ROJO && indice_d == VERDE) {
    tarj = DERECHA_TARJETA;
    melodia(4);
  } else if ( indice_i == VERDE && indice_d == VERDE) {
    tarj = AVANZAR_TARJETA;
    melodia(4);
  } else {
    tarj = ERR_TARJETA;
    melodia(4);
  }
  for (int x = 0; x < FASE; x++) {
    Serial.print(color_d [x]);
    Serial.print("  ");
    Serial.println(color_i [x]);
  }
  reset_tarjetas ();
  Serial.println("CALCULADO");
}

void reset_tarjetas () {
  for (int x = 0; x < FASE; x++) {
    color_d [x] = 0;
    color_i [x] = 0;
  }
}

boolean podemos_leer_tarjeta() {
#define TRESHOLD_LDR 400
#define VECES_LDR 3
#define TIME_COLOR 30
#define VECES_COLOR 7
#define ESPERA_A_SACAR 10
  static unsigned long tiempo_anterior = 0;
  static byte contador_ldr = 0;
  static unsigned long lectura_ldr = 0;
  static byte fase = 0;
  static boolean hay_tarjeta = false;
  static byte contador_color = 0;
  static boolean por_mostrar = true;
  static boolean primera_lectura = true;
  static unsigned long espera_a_sacar = 0;
  static boolean calculado = false;
  if ((millis() - tiempo_anterior) > TIME_COLOR) {
    tiempo_anterior = millis();
    if (hay_tarjeta && !calculado) {
      if (primera_lectura) {
        if (contador_color < ESPERA_A_SACAR)
          contador_color ++;
        else {
          primera_lectura = false;
          contador_color = 0;
          reset_tarjetas();
        }
      } else {
        if (contador_color == 0) {
          switch (fase) {
            case ROJO:
              rojo();
              break;
            case VERDE:
              verde();
              break;
            case AZUL:
              azul();
              break;
          }
        }
        color_d[fase] += leer_color(D);
        color_i[fase] += leer_color(I);
        Serial.print(fase);
        Serial.print("  ");
        Serial.print(contador_color);
        Serial.println(color_d[fase]);
        if (contador_color >= VECES_COLOR) {
          color_d[fase] = color_d[fase] >> 3;
          color_i[fase] = color_i[fase] >> 3;
          Serial.println(color_d[fase]);
          contador_color = 0;
          fase++;
        }
        else
          contador_color++;
        if (fase >= FASE) {
          fase = 0;
          calcular();
          calculado = true;
          hay_tarjeta = false;
          primera_lectura = true;
        }
      }
    }
    else {
      reset_tarjetas ();
      fase = 0;
      contador_color = 0;
    }
    lectura_ldr += analogRead(LDR_1);
    lectura_ldr += analogRead(LDR_2);
    if (contador_ldr >= VECES_LDR) {
      lectura_ldr = lectura_ldr >> 4;
      contador_ldr = 0;
      hay_tarjeta = (lectura_ldr > TRESHOLD_LDR);
      lectura_ldr = 0;
      if (calculado) {
        if (por_mostrar) {
          Serial.println("LISTO");
          por_mostrar = false;
        }
        if (!hay_tarjeta) {
          if (espera_a_sacar > ESPERA_A_SACAR) {
            podemos_leer_tarj = true;
            espera_a_sacar = 0;
            por_mostrar = true;
            calculado = false;
          }
          else
            espera_a_sacar ++;
        }
      }
    } else
      contador_ldr++;
  }
  if (hay_tarjeta) {
    if (por_mostrar) {
      mostrar_procesando();
    }
    else {
      mostrar_listo();
    }
  }
  else if (!podemos_leer_tarj) {
    mostrar_circulo_gradiente();
  }
  return podemos_leer_tarj;
}
