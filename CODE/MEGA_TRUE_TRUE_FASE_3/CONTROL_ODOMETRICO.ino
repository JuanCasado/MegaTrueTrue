#define GIRO 157
#define AVANCE 60
#define L 0.039269
#define G 0.285599

int d_anterior = 0;
int d_inc = 0;
int i_anterior = 0;
int i_inc = 0;
double theta = 0;
double distance = 0;

void updateOdom () {
  d_inc = en_d - d_anterior;
  i_inc = en_i - i_anterior;
  d_anterior = en_d;
  i_anterior = en_i;
  distance += L * (d_inc + i_inc);
  theta += G * (d_inc - i_inc);
}

void control_odometrico(boolean from)
{
#define SALIR 'X'
#define AVANZAR 'A'
#define RETROCEDER 'R'
#define DERECHA 'D'
#define IZQUIERDA 'I'
#define GO 'G'
#define MARGEN 4

#define MAX_DATA 50  //EXISTE EN SOUND_LINKER.ino

#define TIME_ODOM 90

#define MAX_INTEGRAL 70
#define MAX_CONTADOR 5
#define MAX_TIMES 10
  unsigned long tiempo_anterior = 0;
  char comandos [MAX_DATA];

  int toD = 0;
  int toI = 0;
  int errorD = 0;
  int errorI = 0;
  int integral_d = 0;
  int integral_i = 0;
  int err_ant_d = 0;
  int err_ant_i = 0;
  boolean girar = false;
  int timesInOKD = 0;
  int timesInOKI = 0;
  int toDOD = 0;
  int toDOI = 0;
  
  boolean control = true;
  boolean iniciado = false;
  boolean reset_done = false;
  byte datos = 0;
  byte indice = 0;
  boolean done_d = false;
  boolean done_i = false;

  int contador = 0;
  boolean go_done = from;

  while (control) {
    if (iniciado)
    {
      if (indice >= datos) {
        iniciado = false;
        reset_done = false;
        done_d = false;
        done_i = false;
      } else {
        actualizar_encoders();
        mostrar_circulo_gradiente ();
        actualizar_distancia ();
        if ((millis() - tiempo_anterior) > TIME_ODOM)
        {
          tiempo_anterior = millis();
          if (d_parar()) {
            parar();
          } else {
            switch(comandos[indice]){
              case AVANZAR:
                toD = AVANCE;
                toI = 0;
                girar = false;
              break;
              case RETROCEDER:
                toD = -AVANCE;
                toI = 0;
                girar = false;
              break;
              case DERECHA:
                toD = 0;
                toI = GIRO;
                girar = true;
              break;
              case IZQUIERDA:
                toD = 0;
                toI = -GIRO;
                girar = true;
              break;
            }
            updateOdom ();
            errorD = toD - distance;
            errorI = toI - theta;
            
            integral_d = constrain(integral_d + errorD, -MAX_INTEGRAL, MAX_INTEGRAL);
            integral_i = constrain(integral_i + errorI, -MAX_INTEGRAL, MAX_INTEGRAL);

            if (girar){
              if (abs(errorD) < MARGEN){
                 if (timesInOKD < MAX_TIMES){
                    timesInOKD ++;
                 } else {
                        done_d = true;
                 }
              }else{
                  timesInOKD = 0;
              }
              toDOI = errorI*p_odom_g+integral_i*i_odom_g+(errorI-err_ant_i)*d_odom_g;
            } else {
              if (abs(errorI) < MARGEN){
                 if (timesInOKI < MAX_TIMES){
                    timesInOKI ++;
                 } else {
                        done_i = true;
                 }
              }else {
                 timesInOKI = 0;
              }
              toDOI = errorI*p_odom_i+integral_i*i_odom_i+(errorI-err_ant_i)*d_odom_i;
            }
            toDOD = errorD*p_odom_d+integral_d*i_odom_d+(errorD-err_ant_d)*d_odom_d;
            err_ant_d = errorD;
            err_ant_i = errorI;
            if (toDOD > 0){
              toDOD = constrain(toDOD, vel_min, vel_max);
            } else if (toDOD < 0){
              toDOD = constrain(toDOD, -vel_max, -vel_min);
            }
            Serial.print(p_odom_d);
            Serial.print("  ");
            Serial.print(toDOD);
            Serial.print("  ");
            Serial.println(toDOI);
            mover (toDOD - toDOI, toDOD + toDOI);
            
            //AÑADIR COMPROBACION DE FIN DE ACCIÓN -> done_d / done_i

            if (Serial.available() > 0) {
              if (lectura_serial() == SALIR) {
                indice = datos;
                done_d = false;
                done_i = false;
                integral_i = 0;
                integral_d = 0;
                d_anterior = 0;
                timesInOKD = 0;
                timesInOKI = 0;
                d_inc = 0;
                i_anterior = 0;
                i_inc = 0;
                parar();
                reset_encoders ();
                melodia(3);
              }
            }
            if (done_d && done_i) {
              indice ++;
              done_d = false;
              done_i = false;
              integral_i = 0;
              integral_d = 0;
              d_anterior = 0;
              d_inc = 0;
              i_anterior = 0;
              i_inc = 0;
              timesInOKD = 0;
              timesInOKI = 0;
              parar();
              reset_encoders ();
              contador = 0;
              mostrar_circulo (AZUL_CLARO_);
              melodia(5);
            }
          }
        }
      }
    }
    else {
      if (! reset_done) {
        indice = 0;
        datos = 0;
        reset_done = true;
        done_d = false;
        done_i = false;
        menuOdometria();
        reset_encoders ();
        mostrar_circulo (MORADO_);
        mostrar_circulo (AZUL_CLARO_);
        mostrar_circulo (MORADO_);
      }

      if (go_done) {
        if (podemos_leer_tarjeta()) {
          switch (tarjeta()) {
            case GO_TARJETA:
              iniciado = true;
              go_done = false;
              mostrar_circulo (MORADO_);
              mostrar_circulo (AZUL_CLARO_);
              mostrar_circulo (MORADO_);
              break;
            case AVANZAR_TARJETA:
              if (datos < MAX_DATA) {
                comandos [datos] = AVANZAR;
                datos ++;
                o_avanzar();
              }
              break;
            case RETROCEDER_TARJETA:
              if (datos < MAX_DATA) {
                comandos [datos] = RETROCEDER;
                datos ++;
                o_retroceder();
              }
              break;
            case DERECHA_TARJETA:
              if (datos < MAX_DATA) {
                comandos [datos] = DERECHA;
                datos ++;
                o_derecha();
              }
              break;
            case IZQUIERDA_TARJETA:
              if (datos < MAX_DATA) {
                comandos [datos] = IZQUIERDA;
                datos ++;
                o_izquierda ();
              }
              break;
            case ERR_TARJETA:
              o_err();
          }
        }
      } else {
        go_done = (podemos_leer_tarjeta() && (tarjeta() == GO_TARJETA)) ;
      }
      if (Serial.available() > 0) {
        switch (lectura_serial ()) {
          case SALIR:
            control = false;
            menuPrincipal();
            melodia(4);
            break;
          case AVANZAR:
            if (datos < MAX_DATA) {
              comandos [datos] = AVANZAR;
              datos ++;
              o_avanzar ();
              melodia(4);
            }
            break;
          case RETROCEDER:
            if (datos < MAX_DATA) {
              comandos [datos] = RETROCEDER;
              datos ++;
              o_retroceder ();
              melodia(4);
            }
            break;
          case DERECHA:
            if (datos < MAX_DATA) {
              comandos [datos] = DERECHA;
              datos ++;
              o_derecha();
              melodia(4);
            }
            break;
          case IZQUIERDA:
            if (datos < MAX_DATA) {
              comandos [datos] = IZQUIERDA;
              datos ++;
              o_izquierda();
              melodia(4);
            }
            break;
          case GO:
            iniciado = true;
            melodia(4);
            o_go();
            break;
          case INFO:
            menuOdometria ();
            melodia(4);
            break;
          default:
            Serial.println ("COMANDO ERRONEO");
            melodia(3);
            break;
        }
      }
    }
  }
}

void o_derecha () {
  Serial.println("DERECHA -> OK");
}
void o_izquierda () {
  Serial.println("IZQUIERDA -> OK");
}
void o_avanzar () {
  Serial.println("AVANZAR -> OK");
}
void o_retroceder () {
  Serial.println("RETROCEDER -> OK");
}
void o_go () {
  Serial.println("GO -> OK");
}
void o_err () {
  Serial.println("ERR TARJETA");
}
