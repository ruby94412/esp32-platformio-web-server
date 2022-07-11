#include <AsyncEventSource.h>
#include <ArduinoJson.h>
#include <AsyncJson.h>
#include "asyncServer.h"
#include "deviceBridge.h"


AsyncWebServer server(80);
void getJSONResponse(AsyncWebServerRequest *request) {
  DynamicJsonDocument doc(512);
  doc["status"] = "success";
  doc["name"] = "hello word";
  String buf;
  serializeJson(doc, buf);
  request->send(200, "application/json", buf);
}


void handleNotFound(AsyncWebServerRequest *request)
{
    if (request->method() == HTTP_OPTIONS)
    {
        DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "*");
        DefaultHeaders::Instance().addHeader("Access-Control-Max-Age", "10000");
        DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
        DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "*");
        request->send(204);
    }
    else
    {
        request->send(404, "text/plain", "");
    }
}

void listenToPostRequest(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
    String postBody = String((char *)data, len);
    Serial.println(postBody);
    DynamicJsonDocument doc(512);
    DeserializationError error = deserializeJson(doc, postBody);
    if (error) {
        Serial.println(error.c_str());
        String msg = error.c_str();
        request->send(400, "text/plain", "Error in parsin json body!");
    } else {
        JsonObject postObj = doc.as<JsonObject>();
        
        Serial.print("HTTP Method: ");
        Serial.println(request->method());
        if (request->method() == HTTP_POST) {
            if (postObj.containsKey("name") && postObj.containsKey("type")) {
                Serial.println("done.");
                DynamicJsonDocument doc(512);
                doc["status"] = "OK";
                doc["data"] = "post success!!";
                Serial.print("streaming");
                String buf;
                serializeJson(doc, buf);
                request->send(200, "application/json", buf);
                Serial.print("done.");
            }
        }
    }
}

void handleRoot(AsyncWebServerRequest *request) {
  request->send(200, "text/plain", temperature);
}

void startWebServer() {
  server.on("/", HTTP_GET, handleRoot);

  server.on("/json", HTTP_GET, getJSONResponse);
  server.on("/postTest", HTTP_POST, [](AsyncWebServerRequest * request){}, NULL, listenToPostRequest);
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "*");
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}