#define GIRO 250
#define AVANCE 467

long error_odom_d (int goto_d) {
  return goto_d - en_d;
}

long error_odom_i (int goto_i) {
  return goto_i - en_i;
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

#define MAX_INTEGRAL 50
#define MAX_CONTADOR 5
  unsigned long tiempo_anterior = 0;
  char comandos [MAX_DATA];

  long errorD = 0;
  long errorI = 0;
  boolean control = true;
  boolean iniciado = false;
  boolean reset_done = false;
  byte datos = 0;
  byte indice = 0;
  boolean done_d = false;
  boolean done_i = false;
  boolean en_margen_d = false;
  boolean en_margen_i = false;

  int integral_d = 0;
  int integral_i = 0;
  int contador = 0;
  long vel_d = 0;
  long vel_i = 0;

  long diferencial = 0;

  boolean go_done = from;
  boolean motor = false;

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
            switch (comandos[indice]) {
              case AVANZAR:
                errorD = error_odom_d (AVANCE);
                errorI = error_odom_i (AVANCE);
                diferencial = en_d - en_i;
                break;
              case RETROCEDER:
                errorD = error_odom_d (-AVANCE);
                errorI = error_odom_i (-AVANCE);
                diferencial = en_d - en_i;
                break;
              case DERECHA:
                errorD = error_odom_d (-GIRO);
                errorI = error_odom_i (GIRO);
                diferencial = (-en_d) - en_i;
                break;
              case IZQUIERDA:
                errorD = error_odom_d (GIRO);
                errorI = error_odom_i (-GIRO);
                diferencial = en_d + en_i;
                break;
            }
            //DERECHO
            if ((done_d = (abs(errorD) < MARGEN))) {
              en_margen_d = true;
              integral_d = 0;
            }
            else {
              if (errorD < INICIO_INTEGRAL) {
                if (errorD > 0) {
                  if (integral_d < 0)
                    integral_d = 0;
                  if (integral_d < MAX_INTEGRAL)
                    integral_d ++;
                }
                else if (errorD < 0) {
                  if (integral_d > 0)
                    integral_d = 0;
                  if (integral_d > -MAX_INTEGRAL)
                    integral_d --;
                }
                else {
                  integral_d = 0;
                }
              }
              else {
                integral_d = 0;
              }
              en_margen_d = false;
            }
            //IZQUIERDO
            if ((done_i = (abs(errorI) < MARGEN))) {
              en_margen_i = true;
              integral_i = 0;
            }
            else {
              if (errorI < INICIO_INTEGRAL) {
                if (errorI > 0) {
                  if (integral_i < MAX_INTEGRAL)
                    integral_i ++;
                }
                else if (errorI < 0) {
                  if (integral_i > -MAX_INTEGRAL)
                    integral_i --;
                }
                else {
                  integral_i = 0;
                }
              }
              else {
                integral_i = 0;
              }
              en_margen_i = false;
            }
            //APLICAR
            if (motor) {
              vel_i = (errorI * p_odom_i) + (integral_i * i_odom_i) + (diferencial * d_odom_i);
              vel_d = (errorD * p_odom_d) + (integral_d * i_odom_d) - (diferencial * d_odom_i);
            } else {
              vel_i = (errorI * p_odom_i) + (integral_i * i_odom_i) + (diferencial * d_odom_i);
              vel_d = (errorD * p_odom_d) + (integral_d * i_odom_d) - (diferencial * d_odom_i);
            }
            motor = !motor;

            if (en_margen_d) {
              mover_motor (D, 0);
            }
            else {
              mover_motor (D, vel_d);
            }
            if (en_margen_i) {
              mover_motor (I, 0);
            }
            else {
              mover_motor (I, vel_i);
            }
            //INFO
            Serial.println("---");
            Serial.print(en_d);
            Serial.print("->");
            Serial.println(errorD);
            Serial.print(en_i);
            Serial.print("->");
            Serial.println(errorI);
            Serial.print (integral_d);
            Serial.print ("  ");
            Serial.println (integral_i);
            Serial.print (vel_d);
            Serial.print ("  ");
            Serial.println (vel_i);
            Serial.println (diferencial);
            Serial2.write('P');
            Serial2.write(map(errorD + errorI,-comandos[indice] ,comandos[indice] ,0 ,200 ));
            if (Serial.available() > 0) {
              if (lectura_serial() == SALIR) {
                indice = datos;
                done_d = false;
                done_i = false;
                integral_i = 0;
                integral_d = 0;
                parar();
                reset_encoders ();
                melodia(3);
              }
            }
            if (Serial2.available() > 0) {
              if (lectura_wifi () == SALIR) {
                indice = datos;
                done_d = false;
                done_i = false;
                integral_i = 0;
                integral_d = 0;
                parar();
                reset_encoders ();
                melodia(3);
              }
            }
            if (done_d && done_i) {
              if (contador > MAX_CONTADOR) {
                indice ++;
                done_d = false;
                done_i = false;
                integral_i = 0;
                integral_d = 0;
                parar();
                reset_encoders ();
                contador = 0;
                mostrar_circulo (AZUL_CLARO_);
                melodia(5);
              }
              else
                contador++;
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
