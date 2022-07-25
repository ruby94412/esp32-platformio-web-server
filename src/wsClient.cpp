#include "wsClient.h"
#include <ArduinoJson.h>
#include "deviceBridge.h"
#include "AsyncEventSource.h"
#include "esp_websocket_client.h"

const esp_websocket_client_config_t ws_cfg = {
    // local test address to be changed when deployed
    .uri = "ws://47.100.26.104/websockets",
    .port = 8080,
};

esp_websocket_client_handle_t client = esp_websocket_client_init(&ws_cfg);

String parseDataToJSONString(String data[], String props[], int len) {
  DynamicJsonDocument doc(512);
  String buf;
  for (int i = 0; i < len; i++) {
    doc[props[i]] = data[i];
  }
  serializeJson(doc, buf);
  return buf;
}

void websocket_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    esp_websocket_event_data_t *data = (esp_websocket_event_data_t *)event_data;
    
    switch (event_id) {
        case WEBSOCKET_EVENT_CONNECTED:
            Serial.println("WEBSOCKET_EVENT_CONNECTED");
            break;
        case WEBSOCKET_EVENT_DISCONNECTED:
            Serial.println("WEBSOCKET_EVENT_DISCONNECTED");
            break;

        case WEBSOCKET_EVENT_DATA:{
        	  Serial.println("WEBSOCKET_EVENT_DATA");
            /*
            *   1.malloc 2.sprintf 3.char * 4.data->data_len
            */
            char * buffer;
            buffer = (char *) malloc(data->data_len * sizeof(char));
            sprintf(buffer, "%.*s", data->data_len, (char *)data->data_ptr);
            DynamicJsonDocument doc(512);
            deserializeJson(doc, buffer);
            if (doc["type"] == "POST") {
              const int data = doc["data"];
              Serial.println(data);
              modbus.writeSingleRegister(0x00, data);
            };
            break;
        }
        
        case WEBSOCKET_EVENT_ERROR:
            Serial.println("WEBSOCKET_EVENT_ERROR");
            break;
    }
}

void startClient() {
  esp_websocket_register_events(client, WEBSOCKET_EVENT_ANY, websocket_event_handler, (void *)client);
  esp_websocket_client_start(client);
}