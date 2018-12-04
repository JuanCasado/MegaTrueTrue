#include <Wire.h>
#define ADD 0x40
#define TIME 1
#define SOUND 0

#define PRECISION 100
byte sine[PRECISION] = {127, 134, 142, 150, 158, 166, 173, 181, 188, 195, 201, 207, 213, 219, 224, 229, 234, 238, 241, 245, 247, 250, 251, 252, 253, 254, 253, 252, 251, 250, 247, 245, 241, 238, 234, 229, 224, 219, 213, 207, 201, 195, 188, 181, 173, 166, 158, 150, 142, 134, 127, 119, 111, 103, 95, 87, 80, 72, 65, 58, 52, 46, 40, 34, 29, 24, 19, 15, 12, 8, 6, 3, 2, 1, 0, 0, 0, 1, 2, 3, 6, 8, 12, 15, 19, 24, 29, 34, 40, 46, 52, 58, 65, 72, 80, 87, 95, 103, 111, 119/*, 123*/};
//ESCALADO DE LAS NOTAS (1024) => { TCCR#B |= (1 << CS#1) | (1 << CS#0);}

#define zDO 151
#define zDO_ 142
#define zRE 134
#define zRE_ 127
#define zMI 119
#define zFA 112
#define zFA_ 106
#define zSOL 100
#define zSOL_ 94
#define zLA 89
#define zLA_ 84
#define zSI 79
#define DO 74
#define DO_ 70
#define RE 66
#define RE_ 62
#define MI 59
#define FA 55
#define FA_ 52
#define SOL 49
#define SOL_ 46
#define LA 43
#define LA_ 41
#define SI 38
#define _DO 36
#define _DO_ 34
#define _RE 32
#define _RE_ 30
#define _MI 28
#define _FA 27
#define _FA_ 25
#define _SOL 23
#define _SOL_ 22
#define _LA 21
#define _LA_ 19
#define _SI 18
#define ZZ 27 //SILENCIO

#define NT 50 //ESPACIO INTER NOTA 120
#define C 100
#define N 200
#define B 400

volatile byte indice = 0;
volatile boolean cambio_nota = false;
volatile int melodia = 2;
volatile int nota = 0;
volatile boolean tocando = true;

#define MAX_NOTA 4
#define MAX_SONG 2

#define MELODIA1 2
volatile unsigned int melodia1S[MELODIA1+2] = {SI,zSI,SI,zSI};
volatile unsigned int melodia1D[MELODIA1+2] = {N,N,N,N};

#define MELODIA2 10
volatile unsigned int melodia2S[MELODIA2+2] = {RE,FA,SI,SOL,_DO,RE,RE,RE,DO,MI,LA,LA};
volatile unsigned int melodia2D[MELODIA2+2] = {C,C,C,C,C,C,C,C,C,C,C,C};

#define MELODIA3 21
volatile unsigned int melodia3S[MELODIA3+2] = {LA,ZZ,LA,LA,_DO,RE,_DO,SI,LA,SOL,FA,_DO,_DO,ZZ,_DO,SOL,_DO,SOL,_DO,SOL,_DO,_RE,SI};
volatile unsigned int melodia3D[MELODIA3+2] = {B,N,N,N,N,N,N,N,N,N,N,N,N,B,N,N,N,N,N,N,N,N,N};

#define MELODIA4 2
volatile unsigned int melodia4S[MELODIA4+2] = {FA,zSOL,FA,zSOL};
volatile unsigned int melodia4D[MELODIA4+2] = {B,N,B,N};

#define MELODIA5 16
volatile unsigned int melodia5S[MELODIA5+2] = {RE,RE,RE,SOL,_RE,_DO,SI,LA,_SOL,_RE,_DO,SI,LA,_SOL,_RE,_DO,SI,LA};
volatile unsigned int melodia5D[MELODIA5+2] = {C,C,C,B,B,C,C,C,B,N,C,C,C,B,N,C,C,C};

volatile unsigned long tiempo = 0;


void setup() {
  DDRD = B11111111;
  Wire.begin(ADD);
  Wire.onReceive(receiveEvent);
  PORTD = 0;
}

void loop() {
  if((millis() - tiempo) > (cambio_nota ? NT : getDuracion(nota))) {
    if (tocando){
      tiempo = millis();
      if (cambio_nota) {
        setNota (getSound(nota));
        if (nota <= getLen()){
          nota++;
        }
        else{
          nota = 0;
          tocando = false;
        }
      }else{
        setNota (NT);
      }
      cambio_nota = !cambio_nota;
    }
    else{
      setNota (NT);
    }
  }
}

ISR(TIMER1_COMPA_vect) {
  static byte indice = 0;
  if ((!sine[indice]) && (cambio_nota || (getSound(nota) == ZZ))) {
    PORTD = 0;
  } else {
    PORTD = sine[indice];
    if (indice > PRECISION-1) {
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
    tocando = true;
    melodia = song;
}

unsigned int getSound (int pos){
  switch(melodia){
    case 1:
      return melodia1S[pos];
    case 2:
      return melodia2S[pos];
    case 3:
      return melodia3S[pos];
    case 4:
      return melodia4S[pos];
    case 5:
      return melodia5S[pos];
  }
  return 0;
}
unsigned int getDuracion (int pos){
  switch(melodia){
    case 1:
      return melodia1D[pos];
    case 2:
      return melodia2D[pos];
    case 3:
      return melodia3D[pos];
    case 4:
      return melodia4D[pos];
    case 5:
      return melodia5D[pos];
  }
  return 0;
}
int getLen (){
  switch(melodia){
    case 1:
      return MELODIA1;
    case 2:
      return MELODIA2;
    case 3:
      return MELODIA3;
    case 4:
      return MELODIA4;
    case 5:
      return MELODIA5;
  }
  return 0;
}
