#define DIST_D A2
#define DIST_I A3

#define MIN_DISTANCE 95

int distancia_d = 0;
int distancia_i = 0;

void actualizar_distancia () {
#define TIME_DIST 5
#define MAX_MEDIDA_DIST 7
  static long dist_d = 0;
  static long dist_i = 0;
  static byte contador = 0;
  static unsigned long tiempo_anterior = 0;
  if ((millis() - tiempo_anterior) > TIME_DIST) {
    tiempo_anterior = millis();
    dist_d += analogRead(DIST_D);
    dist_i += analogRead(DIST_I);
    if (contador < MAX_MEDIDA_DIST) {
      contador++;
    } else {
      contador = 0;
      distancia_d = (dist_d >> 3);
      distancia_i = (dist_d >> 3);
      dist_d = 0;
      dist_i = 0;
    }
  }
}

boolean d_parar() {
  if ((distancia_d < MIN_DISTANCE) || (distancia_i < MIN_DISTANCE)) {
    Serial.println("PARADA POR OBSTACULO");
    Serial.print(distancia_d);
    Serial.print("  ");
    Serial.println(distancia_i);
    return true;
  }
  return false;
}
