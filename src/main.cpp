#include <Arduino.h>
#include <WiFi.h>
#include "asyncServer.h"
// #include "localWebServer.h"

#define STASSID "anjia_5G"
#define STAPSK "64595969"

// AsyncWebServer server(80);
const char* ssid = STASSID;
const char* password = STAPSK;

// WebServer server(80);

// void getJSONResponse() {
//   DynamicJsonDocument doc(512);
//   doc["status"] = "success";
//   doc["name"] = "hello word";
//   String buf;
//   serializeJson(doc, buf);
//   server.send(200, "application/json", buf);
// }


// void handleNotFound()
// {
//     if (server.method() == HTTP_OPTIONS)
//     {
//         server.sendHeader("Access-Control-Allow-Origin", "*");
//         server.sendHeader("Access-Control-Max-Age", "10000");
//         server.sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
//         server.sendHeader("Access-Control-Allow-Headers", "*");
//         server.send(204);
//     }
//     else
//     {
//         server.send(404, "text/plain", "");
//     }
// }

// void listenToPostRequest() {
//     String postBody = server.arg("plain");
//     Serial.println(postBody);
//     DynamicJsonDocument doc(512);
//     DeserializationError error = deserializeJson(doc, postBody);
//     if (error) {
//         Serial.println(error.c_str());
//         String msg = error.c_str();
//         server.send(400, "text/plain", "Error in parsin json body!");
//     } else {
//         JsonObject postObj = doc.as<JsonObject>();
//         Serial.print("HTTP Method: ");
//         Serial.println(server.method());
//         if (server.method() == HTTP_POST) {
//             if (postObj.containsKey("name") && postObj.containsKey("type")) {
//                 Serial.println("done.");
//                 DynamicJsonDocument doc(512);
//                 doc["status"] = "OK";
//                 doc["data"] = "post success!!";
//                 Serial.print("streaming");
//                 String buf;
//                 serializeJson(doc, buf);
//                 server.sendHeader("Access-Control-Allow-Origin", "*");
//                 server.send(200, "application/json", buf);
//                 Serial.print("done.");
//             }
//         }
//     }
// }

// void handleRoot() {
//   server.send(200, "text/plain", "temperature");
// }

void setup() {
  // put your setup code here, to run once:
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
  // server.begin();
  // server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
  //   request->send(200, "text/plain", "Hello, world");
  // });
  // server.onNotFound(handleNotFound);
  // server.on("/postTest", HTTP_POST, listenToPostRequest);
  // server.on("/inline", []() {
  //   Serial.println("---------get request------");
  //   server.send(200, "text/plain", "this works as well");
  // });
  // server.begin();
  // Serial.println("HTTP server started");
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println("loop");
  
}
