#define DIST_D A2
#define DIST_I A3

#define MIN_DISTANCE 15

int distancia_d = MIN_DISTANCE;
int distancia_i = MIN_DISTANCE;

void actualizar_distancia () {
#define TIME_DIST 25
#define MAX_MEDIDA_DIST 7
  static long dist_d = 0;
  static long dist_i = 0;
  static byte contador = 0;
  static unsigned long tiempo_anterior = 0;
  if ((millis() - tiempo_anterior) > TIME_DIST) {
    tiempo_anterior = millis();
    dist_d += 13 * pow(analogRead(DIST_D) * 0.0048828125, -1);
    dist_i += 13 * pow(analogRead(DIST_I) * 0.0048828125, -1);
    if (contador >= MAX_MEDIDA_DIST) {
      distancia_d = (dist_d >> 3);
      distancia_i = (dist_i >> 3);
      dist_d = 0;
      dist_i = 0;
      contador = 0;
    } else
      contador++;
  }
}

boolean d_parar() {
  if ((distancia_d < MIN_DISTANCE) && (distancia_i < MIN_DISTANCE)) {
    Serial.println("PARADA POR OBSTACULO");
    Serial.print(distancia_d);
    Serial.print("  ");
    Serial.println(distancia_i);
    melodia(6);
    return true;
  }
  return false;
}
