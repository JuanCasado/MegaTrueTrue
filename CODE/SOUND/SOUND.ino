#include <Wire.h>
#define ADD 0x40
#define TIME 1
#define SOUND 0

#define PRECISION 100
byte sine[PRECISION] = {127, 134, 142, 150, 158, 166, 173, 181, 188, 195, 201, 207, 213, 219, 224, 229, 234, 238, 241, 245, 247, 250, 251, 252, 253, 254, 253, 252, 251, 250, 247, 245, 241, 238, 234, 229, 224, 219, 213, 207, 201, 195, 188, 181, 173, 166, 158, 150, 142, 134, 127, 119, 111, 103, 95, 87, 80, 72, 65, 58, 52, 46, 40, 34, 29, 24, 19, 15, 12, 8, 6, 3, 2, 1, 0, 0, 0, 1, 2, 3, 6, 8, 12, 15, 19, 24, 29, 34, 40, 46, 52, 58, 65, 72, 80, 87, 95, 103, 111, 119/*, 123*/};
//ESCALADO DE LAS NOTAS (1024) => { TCCR#B |= (1 << CS#1) | (1 << CS#0);}
#define DO 37
#define RE 33
#define MI 29
#define FA 28
#define SOL 25
#define LA 22
#define SI 19
#define ZZ 27 //SILENCIO

#define NT 50 //ESPACIO INTER NOTA
#define C 250
#define N 500
#define B 1000

byte indice = 0;
boolean cambio_nota = false;
int melodia = 0;
int nota = 0;

#define MAX_NOTA 7
#define MAX_SONG 1
unsigned int melodias[MAX_SONG][MAX_NOTA][2] = {
  {{DO, N}, {RE, N}, {MI, N}, {FA, N}, {SOL, N}, {LA, N}, {SI, N}}
};

unsigned long tiempo = 0;

void setup() {
  DDRD = B11111111;
  Wire.begin(ADD);
  Wire.onReceive(receiveEvent);
  Serial.begin(115200);
  PORTD = 0;
}

void loop() {
  if ((millis() - tiempo) > (cambio_nota?NT:melodias[melodia][nota][TIME])) {
    tiempo = millis();
    setNota (melodias[melodia][nota][SOUND]);
    if (cambio_nota){
      nota++;
    }
    cambio_nota = !cambio_nota;
  }
}

ISR(TIMER1_COMPA_vect) {
  static byte indice = 0;
  if (!sine[indice] && (cambio_nota || (melodias[melodia][nota][SOUND] == ZZ))) {
    PORTD = 0;
  } else {
    PORTD = sine[indice];
    if (indice > PRECISION) {
      indice = 0;
    } else {
      indice++;
    }
  }
}

void setNota(int nota) {
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = nota;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS11) ;
  TIMSK1 |= (1 << OCIE1A);
  sei();
}

void receiveEvent(int song) {
  if (song < MAX_SONG) {
    melodia = song;
  } else {
    melodia = 0;
  }
}
