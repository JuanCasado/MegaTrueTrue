void libertad () {
#define AVANZAR 'A'
#define RETROCEDER 'R'
#define DERECHA 'D'
#define IZQUIERDA 'I'
#define VEL 'V'
#define PARAR 'P'
#define SALIR 'X'
  char vel = 85;
  boolean control = true;
  menuLibertad();
  while (control) {
    if (Serial.available() > 0) { //CREAR MODO JOYSTICK EN BASE A UNA VEL
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
          melodia(2);
          Serial.println(AVANZAR);
          while (Serial.available() < 1) {
            actualizar_distancia ();
            if (d_parar()) {
              parar();
            } else {
              mover(vel,vel);
            }
            delay (100);
          }
          break;
        case RETROCEDER:
          melodia(2);
          Serial.println(RETROCEDER);
          while (Serial.available() < 1) {
            actualizar_distancia ();
            if (d_parar()) {
              parar();
            } else {
              mover(-vel,-vel);
            }
            delay (100);
          }
          break;
        case DERECHA:
          melodia(2);
          Serial.println(DERECHA);
          while (Serial.available() < 1) {
            actualizar_distancia ();
            if (d_parar()) {
              parar();
            } else {
              mover(-vel,vel);
            }
            delay (100);
          }
          break;
        case IZQUIERDA:
          melodia(2);
          Serial.println(IZQUIERDA);
          while (Serial.available() < 1) {
            actualizar_distancia ();
            if (d_parar()) {
              parar();
            } else {
              mover(vel,-vel);
            }
            delay (100);
          }
          break;
        case INFO:
          menuLibertad ();
          melodia(2);
          break;
        default:
          Serial.println("COMANDO NO VALIDO");
          melodia(4);
          break;
      }
      melodia(2);
    }
  }
}
