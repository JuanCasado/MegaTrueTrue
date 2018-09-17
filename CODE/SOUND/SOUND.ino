#define PRECISION 99
byte sine[] = {127, 134, 142, 150, 158, 166, 173, 181, 188, 195, 201, 207, 213, 219, 224, 229, 234, 238, 241, 245, 247, 250, 251, 252, 253, 254, 253, 252, 251, 250, 247, 245, 241, 238, 234, 229, 224, 219, 213, 207, 201, 195, 188, 181, 173, 166, 158, 150, 142, 134, 127, 119, 111, 103, 95, 87, 80, 72, 65, 58, 52, 46, 40, 34, 29, 24, 19, 15, 12, 8, 6, 3, 2, 1, 0, 0, 0, 1, 2, 3, 6, 8, 12, 15, 19, 24, 29, 34, 40, 46, 52, 58, 65, 72, 80, 87, 95, 103, 111, 119,123};
#define DO 37
#define RE 33
#define MI 29
#define FA 28
#define SOL 25
#define LA 21
#define SI 19
//ESCALADO DE LAS NOTAS (1024) => { TCCR#B |= (1 << CS#1) | (1 << CS#0);}
#define MAX_NOTA 6

/*
#define MAX_DATA 50
#define SELECCIONAR 'S'
#define REPRODUCIR 'R'
#define PARAR 'P'
#define COMPROBAR 'C'*/

byte indice = 0;
boolean tocando = true;
boolean cambio_nota = false;
boolean error = false;
int melodia = 0;
int nota = 0;
//char comandos [MAX_DATA];
int melodias[][7] = {
  {DO, RE, MI, FA, SOL, LA, SI}
};

void setup() {
  DDRD = B11111111;
  setNota(DO);
}

void loop() {

 
  if (cambio_nota){
    setNota (melodias[melodia][nota]);
    cambio_nota = false;
  }



/*if (Serial.available() > 0)
  {
    switch (comandos[indice]) //Completar
    {
      case SELECCIONAR: 
        switch(comandos_melodias[indice_melodias])
          {
            case MELODIA1
            break;
            case DO
            break;
          }
      break;
      case REPRODUCIR:
      break;
      case PARAR:
      break;
      case COMPROBAR:
      if(tocando == true)
        Serial.print('S');
      else
        Serial.print('N');
      break;
    }*/

  
}

ISR(TIMER1_COMPA_vect) {
  static byte indice = 0;
  if (tocando) {
    PORTD = sine[indice];
    if (indice >= PRECISION) {
      indice = 0;
      if (nota >= MAX_NOTA) {
        nota = 0;
        //tocando = false;
      } else {
        nota++;
      }
    cambio_nota = true;
    } else {
      indice++;
    }
  } else {
    PORTD = 0;
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
