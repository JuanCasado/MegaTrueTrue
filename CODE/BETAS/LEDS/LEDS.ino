#include <Adafruit_NeoPixel.h>
#define PIN           9
#define NUMPIXELS     16
#define D 0
#define I 1

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
uint32_t ROJO_ = pixels.Color(255,0,0);
uint32_t VERDE_ = pixels.Color(0,255,0);
uint32_t AZUL_OSCURO_ = pixels.Color(0,0,255);
uint32_t BLANCO_ = pixels.Color(255,255,255);
uint32_t AMARILLO_ = pixels.Color(255,255,0);
uint32_t MORADO_ = pixels.Color(255,0,255);
uint32_t AZUL_CLARO_ = pixels.Color(0,0,255);
void setup() {
  pixels.begin();
}

void loop() {
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0,150,0));
    pixels.show(); 
  }
}

void mostrar_circulo (uint32_t color){
#define T_CIRCULO 100
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, color);
    pixels.show(); 
    delay (T_CIRCULO);
  }
}
void mostrar_pares (uint32_t color){
  for(int i=0;i<NUMPIXELS;i+=2){
    pixels.setPixelColor(i, color);
  }
  pixels.show(); 
}
void mostrar_impares (uint32_t color){
  for(int i=1;i<NUMPIXELS;i+=2){
    pixels.setPixelColor(i, color);
  }
  pixels.show(); 
}
void mostrar_mitad (byte lado,uint32_t color){
  boolean hacer = false;
  byte inicio;
  if (lado == D){
    hacer = true;
    inicio = 0;
  }else if (lado == I){
    hacer = true;
    inicio = NUMPIXELS >> 2;
  }
  if (hacer){
    for(;inicio<NUMPIXELS;inicio++){
      pixels.setPixelColor(inicio, color);
    }
  }
  pixels.show(); 
}
void mostrar_todos (uint32_t color){
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, color);
  }
  pixels.show(); 
}

