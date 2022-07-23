#include "wsClient.h"
#include <ArduinoJson.h>
#include "deviceBridge.h"
#include "AsyncEventSource.h"
#include "esp_websocket_client.h"

const esp_websocket_client_config_t ws_cfg = {
    // local test address to be changed when deployed
    .uri = "ws://192.168.0.37/websockets",
    .port = 8080,
};

esp_websocket_client_handle_t client = esp_websocket_client_init(&ws_cfg);


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

        case WEBSOCKET_EVENT_DATA:
        	  Serial.println("WEBSOCKET_EVENT_DATA");
            Serial.println(data->op_code);
            /*
            *   1.malloc 2.sprintf 3.char * 4.data->data_len
            */
            char * buffer;
            buffer = (char *) malloc(data->data_len * sizeof(char));
            sprintf(buffer, "%.*s", data->data_len, (char *)data->data_ptr);
            Serial.println(buffer);
            // to do: parse string(char *) to JSON

            break;
        
        case WEBSOCKET_EVENT_ERROR:
            Serial.println("WEBSOCKET_EVENT_ERROR");
            break;
    }
}

void startClient() {
  esp_websocket_register_events(client, WEBSOCKET_EVENT_ANY, websocket_event_handler, (void *)client);
  esp_websocket_client_start(client);
}