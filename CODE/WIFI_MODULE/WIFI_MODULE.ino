#include <ESP8266WiFi.h>

#define _SSID "TRUTRUE_AUVERGINE"
#define _PASS "complubot123"
WiFiServer server(80);
WiFiClient client;

bool toSend = false;

#define ADD 0x40
#define MAX_DATA 50 //EXISTE EN MEGATRUETUE.ino!!!
#define MAX_CONF 5 //VOLTS,P_D,I_D,P_I,I_I
char state = 'M';
char buff[MAX_DATA];
char len = 0;
char conf[MAX_CONF];
char percentaje = 0;


void setup() {
  Serial.begin(115200);
  server.begin();
  WiFi.mode(WIFI_AP);
  WiFi.softAP(_SSID, _PASS);
  IPAddress local_ip(192, 168, 1, 1);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.softAPConfig(local_ip, gateway, subnet);
}

void loop() {
  if (client.connected()) {
    toSend = true;
    if (client.available()) {
      String peticion = client.readStringUntil('\r');
      client.print(peticion);
      client.flush();
      for (int x = 0; x < peticion.length(); x++) {
        Serial.write(peticion.charAt(x));
      }
    }
  } else {
    client.stop();
    client = server.available();
    toSend = false;
  }
  if (Serial.available()) { //ELIMINAR LÓGICA INTERMEDIA
    //CREAR UN BUFFER DE RECEPCIÓN DE DATOS PUROS QUE SE ENVÍE EN BASE A UN 
    //CARACTER TERMINADOR RECIBIDO DESDE EL MASTER
    switch (Serial.read() & ~0x20) {
      case 'M': //MENU
        state = (Serial.read() & ~0x20);
        if (toSend) {
          client.println(state);
        }
        break;
      case 'S': //STACK_ODOM
        len = constrain(Serial.read(), 1, MAX_DATA);
        for (char x = 0; x < len; x++) {
          buff[x] = (Serial.read() & ~0x20);
        }
        for (char x = len; x < MAX_DATA; x++) {
          buff[x] = '\0';
        }
        if (toSend) {
          client.println('S' + buff);
        }
        break;
      case 'P': //PERCENTAJE_COMPLETED
        percentaje = Serial.read();
        if (toSend) {
          client.println('P' + percentaje);
        }
        break;
      case 'F': //ODOM_ACTION_FINISHED
        if (toSend) {
          client.println('F');
        }
        break;
      case 'C': //CONFIGURATION
        for (char x = 0; x < MAX_CONF; x++) {
          conf[x] = (Serial.read() & ~0x20);
        }
        if (toSend) {
          client.println('C' + buff);
        }
        break;
      case 'X': //OBSTACULO
        if (toSend) {
          client.println('X');
        }
        break;
    }
  }
}
