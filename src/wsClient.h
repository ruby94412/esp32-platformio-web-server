#include <WebSocketsClient.h>
#include "esp_websocket_client.h"
#ifndef WSCLIENT_H /* include guards */
#define WSCLIENT_H

void startClient();
extern esp_websocket_client_handle_t client;

#endif /* WSCLIENT_H */