#define ESPERA 8
void menuPrincipal () {
  Serial.println("Mega_True_True");
  Serial.println("ODOMETRIA O");
  Serial.println("CONFIGURACION M");
  Serial.println("LIBERTAD L");
  melodia(2);
}
void menuOdometria () {
  Serial.println("Odometria");
  Serial.println("AVANZAR A");
  Serial.println("RETROCEDER R");
  Serial.println("DERECHA D");
  Serial.println("IZQUIERDA I");
  Serial.println("GO G");
  melodia(2);
}
void menuLibertad () {
  Serial.println("Libertad");
  Serial.println("AVANZAR 'A'");
  Serial.println("RETROCEDER 'R'");
  Serial.println("DERECHA 'D'");
  Serial.println("IZQUIERDA 'I'");
  Serial.println("VEL 'V'");
  Serial.println("PARAR 'P'");
  melodia(2);
}
void menuConfiguracion () {
  Serial.println("Configuracion");
  Serial.println("VELOCIDAD_MAX 'A'");
  Serial.println("VELOCIDAD_MIN 'B'");
  Serial.println("P_ODOM_D 'C'");
  Serial.println("I_ODOM_D 'D'");
  Serial.println("P_ODOM_D 'E'");
  Serial.println("P_ODOM_I 'F'");
  Serial.println("I_ODOM_I 'G'");
  Serial.println("P_ODOM_I 'H'");
  Serial.println("P_ODOM_G 'I'");
  Serial.println("I_ODOM_G 'J'");
  Serial.println("P_ODOM_G 'K'");
  Serial.println("SAVE 'S'");
  melodia(2);
}
