#define T_ODOM 50
#define T_ODOM_MAX 10000
#define FR 0.08595
#define GR 0.31144
#define PF 1.1
#define IF 0.012
#define PG 1.2
#define IG 0.03
#define PGA 0.1
#define IGA 0.01
#define MARGEN 6

unsigned long t_odom = 0;
unsigned long enter_odom = 0;
double pos_f = 0;
double pos_g = 0;
bool done = true;
long en_d_a = 0;
long en_i_a = 0;
int error_f = 0;
int error_g = 0;
int error_f_i = 0;
int error_g_i = 0;
int error_f_a = 0;
int error_g_a = 0;
int move_f = 0;
int move_g = 0;

void update_pos() {
  pos_f += ((en_d - en_d_a) + (en_i - en_i_a)) * FR;
  pos_g += ((en_d - en_d_a) - (en_i - en_i_a)) * GR;
  en_d_a = en_d;
  en_i_a = en_i;
}

void odom (int forward, int giro) {
  pos_f = 0;
  pos_g = 0;
  done = true;
  en_d_a = 0;
  en_i_a = 0;
  error_f_i = 0;
  error_g_i = 0;
  error_f_a = 0;
  error_g_a = 0;
  reset_encoders ();
  enter_odom = millis();
  while (done) {
    actualizar_distancia ();
    if ((millis() - T_ODOM) > t_odom) {
      t_odom = millis();
      en_d = leerEncoder_d();
      en_i = leerEncoder_i();
      update_pos();
      error_f = forward - pos_f;
      error_g = giro - pos_g;

      if (abs(error_f) > 1) {
        error_f_i += error_f;
      } else {
        if (error_f > 0)
          error_f_i ++;
        else
          error_f_i --;
      }
      if (abs(error_g) > 1) {
        error_g_i += error_g;
      } else {
        if (error_g > 0)
          error_g_i ++;
        else
          error_g_i --;
      }

      Serial.print(error_f);
      Serial.print("  ");
      Serial.println(error_g);
      Serial.print(error_f_i);
      Serial.print("  ");
      Serial.println(error_g_i);
      Serial.println("  ");

      move_f = error_f * PF + error_f_i * IF;
      move_f = constrain(move_f, -vel_max, vel_max);
      if (!giro) {
        move_g = error_g * PGA + error_g_i * IGA;
      } else {
        move_g = error_g * PG + error_g_i * IG;
      }

      mover (move_f - move_g, move_f + move_g);
      if (giro == 0) {
        if (abs(error_f) < MARGEN)
          done = false;
      } else {
        if (abs(error_g) < MARGEN)
          done = false;
      }
      if ((enter_odom + T_ODOM_MAX) < millis()) {
        done = false;
      }
    }
  }
}
