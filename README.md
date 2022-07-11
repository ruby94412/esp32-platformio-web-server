# esp32-platformio-web-server

1. based on platformio and esp32 wroom
2. lib depends: a.ArduinoJson b.ESPAsybcWebServer c.ModbusMaster (version details from "platformio.ini")
3. hardware pins connection: <br/>
<table>
<thead>
<tr>
<th>MAX485(Serial transceiver)</th>
<th>ESP-WROOM-32(wifi module)</th>
</tr>
</thead>
<tbody>
<tr>
<td align="center">VCC</td>
<td align="center">3v3</td>
</tr>
<tr>
<td align="center">GND</td>
<td align="center">GND</td>
</tr>
<tr>
<td align="center">DI</td>
<td align="center">TX2(GPIO 17)</td>
</tr>
<tr>
<td align="center">RO</td>
<td align="center">RX2(GPIO 16)</td>
</tr>
<tr>
<td align="center">RE/DE</td>
<td align="center">D4(GPIO 4)</td>
</tr>
</tbody>
</table>
(A&B ports from MAX485 to the rs485 supported device)
