void libertad () {
#define AVANZAR 'A'
#define RETROCEDER 'R'
#define DERECHA 'D'
#define IZQUIERDA 'I'
#define AVANZAR1 'B'
#define RETROCEDER1 'E'
#define DERECHA1 'F'
#define IZQUIERDA1 'L'
#define VEL 'V'
#define PARAR 'P'
#define SALIR 'X'
  char vel = 40;
  boolean control = true;
  menuLibertad();
  while (control) {
    if (Serial.available() > 0) {
      switch (lectura_serial ()) {
        case SALIR:
          control = false;
          break;
        case PARAR:
          Serial.println(PARAR);
          parar();
          break;
        case VEL:
          Serial.print("VEL = ");
          vel = read_number(true);
          Serial.print((int)vel);
          break;
        case AVANZAR:
          Serial.println(AVANZAR);
          while (Serial.available() < 1) {
            actualizar_distancia ();
            if (d_parar()) {
              parar();
            } else {
              mover_motor (D, vel);
              mover_motor (I, vel);
              delay (100);
            }
          }
          break;
        case RETROCEDER:
          Serial.println(RETROCEDER);
          while (Serial.available() < 1) {
            actualizar_distancia ();
            if (d_parar()) {
              parar();
            } else {
              mover_motor (D, -vel);
              mover_motor (I, -vel);
              delay (100);
            }
          }
          break;
        case DERECHA:
          Serial.println(DERECHA);
          while (Serial.available() < 1) {
            actualizar_distancia ();
            if (d_parar()) {
              parar();
            } else {
              mover_motor (D, -vel);
              mover_motor (I, vel);
              delay (100);
            }
          }
          break;
        case IZQUIERDA:
          Serial.println(IZQUIERDA);
          while (Serial.available() < 1) {
            actualizar_distancia ();
            if (d_parar()) {
              parar();
            } else {
              mover_motor (D, vel);
              mover_motor (I, -vel);
              delay (100);
            }
          }
          break;
        case AVANZAR1:
          Serial.println(AVANZAR1);
          reset_encoders();
          while ((error_odom_d (AVANCE) > 0) && (error_odom_i (AVANCE) > 0)) {
            actualizar_distancia ();
            if (d_parar()) {
              parar();
            } else {
              mover_motor (D, vel);
              mover_motor (I, vel);
              delay (100);
              en_d = leerEncoder_d();
              en_i = leerEncoder_i();
            }
          }
          parar();
          reset_encoders();
          break;
        case RETROCEDER1:
          Serial.println(RETROCEDER1);
          reset_encoders();
          while ((error_odom_d (-AVANCE) < 0) && (error_odom_i (-AVANCE) < 0)) {
            actualizar_distancia ();
            if (d_parar()) {
              parar();
            } else {
              mover_motor (D, -vel);
              mover_motor (I, -vel);
              delay(100);
              en_d = leerEncoder_d();
              en_i = leerEncoder_i();
            }
          }
          parar();
          reset_encoders();
          break;
        case DERECHA1:
          Serial.println(DERECHA1);
          reset_encoders();
          while ((error_odom_d (-GIRO) < 0) && (error_odom_i (GIRO) > 0)) {
            actualizar_distancia ();
            if (d_parar()) {
              parar();
            } else {
              mover_motor (D, -vel);
              mover_motor (I, vel);
              delay (100);
              en_d = leerEncoder_d();
              en_i = leerEncoder_i();
            }
          }
          parar();
          reset_encoders();
          break;
        case IZQUIERDA1:
          Serial.println(IZQUIERDA1);
          reset_encoders();
          while ((error_odom_d (GIRO) > 0) && (error_odom_i (-GIRO) < 0)) {
            actualizar_distancia ();
            if (d_parar()) {
              parar();
            } else {
              mover_motor (D, vel);
              mover_motor (I, -vel);
              delay(100);
              en_d = leerEncoder_d();
              en_i = leerEncoder_i();
            }
          }
          parar();
          reset_encoders();
          break;
        case INFO:
          menuLibertad ();
          break;
        default:
          Serial.println("COMANDO NO VALIDO");
          break;
      }
    }
  }
}

