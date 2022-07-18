#include <Arduino.h>
#include <WiFiClientSecure.h>
#include "asyncServer.h"
#include "deviceBridge.h"
#include "wsClient.h"

#define STASSID "anjia_5G"
#define STAPSK "64595969"
const int port = 443;

const char* ssid = STASSID;
const char* password = STAPSK;


void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);      
  WiFi.begin(ssid, password);
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
  startModbus();
  startClient();
}

void loop() {
  modbusInLoop();
}
