#include <Arduino.h>
#include <WiFi.h>
#include "asyncServer.h"

#define STASSID "anjia_5G"
#define STAPSK "64595969"

const char* ssid = STASSID;
const char* password = STAPSK;


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("monitor");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  startWebServer();
}

void loop() {
}
