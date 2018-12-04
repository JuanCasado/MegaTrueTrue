#define LDR_1 A0
#define LDR_2 A1
#define TIME 20
#define VECES 3
#define TRESHOLD 400

unsigned long lectura_ldr = 0;
unsigned long tiempo_anterior = 0;
byte contador = 0;

void setup(){
  Serial.begin(115200);
}

void loop(){
  if ((millis()-tiempo_anterior)>TIME){
    tiempo_anterior = millis();
    lectura_ldr += analogRead(LDR_1);
    lectura_ldr += analogRead(LDR_2);
   
    if (contador >= VECES){
      lectura_ldr = lectura_ldr >> 4;
      contador = 0;
      Serial.println(lectura_ldr>TRESHOLD?"HAY_TARJETA":"NO HAY_TARJETA");
      lectura_ldr = 0;
    }else{
      contador++;
    }
  }
}
