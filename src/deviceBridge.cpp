#include "ModbusMaster.h"
#include "deviceBridge.h"
#include "wsClient.h"
#include "esp_websocket_client.h"

#define MAX485_RE_NEG  4 
#define Slave_ID       1    
#define RX_PIN         16   //RX2 
#define TX_PIN         17   //TX2

ModbusMaster modbus;

long lastMillis = 0;
String temperature = "";

void preTransmission()
{
  digitalWrite(MAX485_RE_NEG, HIGH); //Switch to transmit data
}
void postTransmission()
{
  digitalWrite(MAX485_RE_NEG, LOW); //Switch to receive data
}

void startModbus() {
  pinMode(MAX485_RE_NEG, OUTPUT);
  // Init in receive mode
  digitalWrite(MAX485_RE_NEG, LOW);
  // Modbus communication runs at 9600 baud
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  modbus.begin(Slave_ID, Serial2);
  modbus.preTransmission(preTransmission);
  modbus.postTransmission(postTransmission);
}

bool getResultMsg(ModbusMaster *node, uint8_t result) 
{
  String tmpstr2 = "\r\n";
  switch (result) 
  {
  case node->ku8MBSuccess:
    return true;
    break;
  case node->ku8MBIllegalFunction:
    tmpstr2 += "Illegal Function";
    break;
  case node->ku8MBIllegalDataAddress:
    tmpstr2 += "Illegal Data Address";
    break;
  case node->ku8MBIllegalDataValue:
    tmpstr2 += "Illegal Data Value";
    break;
  case node->ku8MBSlaveDeviceFailure:
    tmpstr2 += "Slave Device Failure";
    break;
  case node->ku8MBInvalidSlaveID:
    tmpstr2 += "Invalid Slave ID";
    break;
  case node->ku8MBInvalidFunction:
    tmpstr2 += "Invalid Function";
    break;
  case node->ku8MBResponseTimedOut:
    tmpstr2 += "Response Timed Out";
    break;
  case node->ku8MBInvalidCRC:
    tmpstr2 += "Invalid CRC";
    break;
  default:
    tmpstr2 += "Unknown error: " + String(result);
    break;
  }
  Serial.println(tmpstr2);
  return false;
}

void modbusInLoop() 
{
  long currentMillis = millis();
  if (currentMillis - lastMillis > 1000) 
  {
    uint8_t result = modbus.readInputRegisters(0x00, 6);
    // modbus.writeSingleRegister(0x00, 100);
    if (getResultMsg(&modbus, result)) 
    {
      String dataList[2];
      String props[2];
      dataList[0] = String(((double)modbus.getResponseBuffer(0)) / 10);
      dataList[1] = String(((double)modbus.getResponseBuffer(3)) / 10);
      props[0] = "temperture";
      props[1] = "sv";
      String data = parseDataToJSONString(dataList, props, 2);
      Serial.println(data);
      // webSocketsClient.sendTXT(temperature);
      esp_websocket_client_send_text(client, data.c_str(), data.length(), 10000);
    
    }
    lastMillis = currentMillis;
  }
}