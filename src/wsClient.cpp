#include "wsClient.h"
#include "WebSocketsClient.h"
#include <ArduinoJson.h>
#include "deviceBridge.h"
#include "AsyncEventSource.h"
#include "esp_websocket_client.h"

const esp_websocket_client_config_t ws_cfg = {
    .uri = "ws://47.100.26.104/websockets",
    .port = 8080,
};

WebSocketsClient wsc;

esp_websocket_client_handle_t client = esp_websocket_client_init(&ws_cfg);

void startClient() {
  // wsc.begin("ws://192.168.0.37", 8080, "/");
  // Serial.println(wsc.isConnected());
  esp_websocket_client_start(client);
  Serial.println(esp_websocket_client_is_connected(client));
}