void mostrar_circulo (uint32_t color) {
#define T_CIRCULO 50
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, color);
    pixels.show();
    delay (T_CIRCULO);
  }
}
void mostrar_circulo_gradiente () {
#define T_CIRCULO_G 20
  static unsigned long tiempo_anterior = 0;
  static byte color = 0;
  static boolean marcha_atras = false;
  if ((millis() - tiempo_anterior) > T_CIRCULO_G) {
    tiempo_anterior = millis();
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 255, color));
    }
    if (marcha_atras)
      color --;
    else
      color ++;
    if (color == 255)
      marcha_atras = true;
    if (color == 0)
      marcha_atras = false;
    pixels.show();
  }
}
void mostrar_circulo_error () {
#define T_CIRCULO_E 30
  static unsigned long tiempo_anterior = 0;
  static byte color = 0;
  if ((millis() - tiempo_anterior) > T_CIRCULO_G) {
    tiempo_anterior = millis();
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(color, 0, 50));
    }
    pixels.show();
  }
  if (color == 255)
    error = false;
  color++;
}
void mostrar_procesando () {
#define T_CIRCULO_P 20
  static unsigned long tiempo_anterior = 0;
  static byte i = 0;
  clear_light();
  if ((millis() - tiempo_anterior) > T_CIRCULO_E) {
    tiempo_anterior = millis();
    pixels.setPixelColor(i, color);
    i ++;
    if (i >= NUMPIXELS) {
      i = 0;
    }
    pixels.show();
  }
}
void mostrar_listo () {
#define T_CIRCULO_L 20
  static unsigned long tiempo_anterior = 0;
  static byte a = 0;
  static byte b = NUMPIXELS / 4;
  static byte c = NUMPIXELS / 2;
  static byte d = (NUMPIXELS / 4) * 3;
  clear_light();
  if ((millis() - tiempo_anterior) > T_CIRCULO_E) {
    tiempo_anterior = millis();
    pixels.setPixelColor(a, color);
    pixels.setPixelColor(b, color);
    pixels.setPixelColor(c, color);
    pixels.setPixelColor(d, color);
    a ++;
    b ++;
    c ++;
    d ++;
    if (a >= NUMPIXELS) {
      a = 0;
    }
    if (b >= NUMPIXELS) {
      b = 0;
    }
    if (c >= NUMPIXELS) {
      c = 0;
    }
    if (d >= NUMPIXELS) {
      d = 0;
    }
    pixels.show();
  }
}
void mostrar_pares (uint32_t color) {
  for (int i = 0; i < NUMPIXELS; i += 2) {
    pixels.setPixelColor(i, color);
  }
  pixels.show();
}
void mostrar_impares (uint32_t color) {
  for (int i = 1; i < NUMPIXELS; i += 2) {
    pixels.setPixelColor(i, color);
  }
  pixels.show();
}
void mostrar_mitad (byte lado, uint32_t color) {
  boolean hacer = false;
  byte inicio;
  if (lado == D) {
    hacer = true;
    inicio = 0;
  } else if (lado == I) {
    hacer = true;
    inicio = NUMPIXELS >> 2;
  }
  if (hacer) {
    for (; inicio < NUMPIXELS; inicio++) {
      pixels.setPixelColor(inicio, color);
    }
  }
  pixels.show();
}
void mostrar_todos (uint32_t color) {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, color);
  }
  pixels.show();
}
void clear_light() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, APAGADO_);
  }
}
