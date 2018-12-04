#include <ESP8266WiFi.h>

#define _SSID "TRUTRUE_AUVERGINE"
#define _PASS "complubot123"
WiFiServer server(5003);
WiFiClient client;

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
    if (client.available()) {
      String peticion = client.readStringUntil('\r');
      client.flush();
      if (peticion.length() < 5){
        for (unsigned int x = 0; x < peticion.length(); x++) {
          Serial.write(peticion.charAt(x));
        }
      }
    }
  } else {
    client.stop();
    client = server.available();
  }
}
