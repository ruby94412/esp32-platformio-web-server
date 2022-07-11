# esp32-platformio-web-server

1. based on platformio and esp32 wroom
2. lib depends: a.ArduinoJson b.ESPAsybcWebServer c.ModbusMaster (version details from "platformio.ini")
3. hardware pins connection: 
   MAX485(Serial transceiver)   ESP-WROOM-32(wifi module)
          VCC                          3v3
          GND                          GND
          DI                           TX2(GPIO 17)
          R0                           RX2(GPIO 16)
          RE/DE                        D4(GPIO 4)
   (A&B ports from MAX485 to the rs485 supported device)
 
