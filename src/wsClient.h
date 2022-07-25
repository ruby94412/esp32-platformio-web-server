#include <WebSocketsClient.h>
#include "esp_websocket_client.h"
#ifndef WSCLIENT_H /* include guards */
#define WSCLIENT_H

void startClient();
String parseDataToJSONString(String data[], String props[], int len);
extern esp_websocket_client_handle_t client;

#endif /* WSCLIENT_H */