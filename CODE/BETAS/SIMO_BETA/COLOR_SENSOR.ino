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
byte leer_d () {
  return (byte)(MAX_BYTE - constrain(pulseIn(OUT_D, LOW), 0, MAX_BYTE));
}
byte leer_i () {
  return (byte)(MAX_BYTE - constrain(pulseIn(OUT_I, LOW), 0, MAX_BYTE));
}

void calcular () {
  byte der = 0;
  byte izq = 0;
  boolean negro_d = true;
  boolean negro_i = true;

  for (int x = 0; x < 2; x++) {
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

  if (negro_i && indice_d == ROJO){
    tarjeta = GO;
  } else if ( indice_i == ROJO && indice_d == ROJO){
    tarjeta = RETROCEDER;
  }else if ( indice_i == VERDE && indice_d == ROJO){
    tarjeta = IZQUIERDA;
  }else if ( indice_i == ROJO && indice_d == VERDE){
    tarjeta = DERECHA;
  }else if ( indice_i == VERDE && indice_d == VERDE){
    tarjeta = AVANZAR;
  }else{
    tarjeta = ERR;
  }
  reading = false;
}

void reset () {
  for (int x = 0; x < FASE; x++) {
    color_d [x] = 0;
    color_i [x] = 0;
  }
}



void color_run(){
  if ((millis() - tiempo_anterior_color) > TIME) {
    tiempo_anterior_color = millis();
    if (hay_tarjeta) {
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
      color_d[fase] += leer_d();
      color_i[fase] += leer_i();
      //Serial.println(color_d[fase]);
      delay(5);
      if (contador_color >= VECES_COLOR) {
        color_d[fase] = color_d[fase] >> 3;
        color_i[fase] = color_i[fase] >> 3;
        contador_color = 0;
        fase++;
      }
      else {
        contador_color++;
      }
      if (fase >= FASE) {
        fase = 0;
        /*
        Serial.print("R -> ");
        Serial.print("I: ");
        Serial.print(color_i[ROJO]);
        Serial.print(" D: ");
        Serial.println(color_d[ROJO]);
        Serial.print("G -> ");
        Serial.print("I: ");
        Serial.print(color_i[VERDE]);
        Serial.print(" D: ");
        Serial.println(color_d[VERDE]);
        Serial.print("B -> ");
        Serial.print("I: ");
        Serial.print(color_i[AZUL]);
        Serial.print(" D: ");
        Serial.println(color_d[AZUL]);
        */
        calcular();
        /*
        Serial.print("I -> ");
        switch (indice_i) {
          case ROJO:
            Serial.print("ROJO");
            break;
          case VERDE:
            Serial.print("VERDE");
            break;
          case AZUL:
            Serial.print("AZUL");
            break;
        }
        Serial.print(" D -> ");
        switch (indice_d) {
          case ROJO:
            Serial.print("ROJO");
            break;
          case VERDE:
            Serial.print("VERDE");
            break;
          case AZUL:
            Serial.print("AZUL");
            break;
        }
        Serial.println("\n------------------------");
        Serial.println();
        switch (tarjeta) {
          case AVANZAR:
            Serial.println("AVANZAR");
            break;
          case RETROCEDER:
            Serial.println("RETROCEDER");
            break;
          case DERECHA:
            Serial.println("DERECHA");
            break;
          case IZQUIERDA:
            Serial.println("IZQUIERDA");
            break;
          case GO:
            Serial.println("GO");
            break;
          case ERR:
            Serial.println("ERR");
            break;
        }
        */
        reset();
      }
    } 
  }
}

void ldr_run(){
  if ((millis() - tiempo_anterior_ldr) > TIME) {
      tiempo_anterior_ldr = millis();
      lectura_ldr += analogRead(LDR_1);
      lectura_ldr += analogRead(LDR_2);
      if (contador_ldr >= VECES_LDR) {
        lectura_ldr = lectura_ldr >> 4;
        //Serial.println(lectura_ldr);
        contador_ldr = 0;
        //Serial.println((hay_tarjeta = (lectura_ldr > TRESHOLD_LDR)) ? "HAY_TARJETA" : "NO HAY_TARJETA");
        hay_tarjeta = (lectura_ldr > TRESHOLD_LDR);
        lectura_ldr = 0;
      } else {
        contador_ldr++;
      }
    }
}
