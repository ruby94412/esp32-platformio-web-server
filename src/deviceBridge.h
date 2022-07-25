#include "ModbusMaster.h"
#ifndef DEVICEBRIDGE_H /* include guards */
#define DEVICEBRIDGE_H

/* blinky initialization function */
void startModbus();
void modbusInLoop();
extern String temperature;
extern ModbusMaster modbus;

#endif /* DEVICEBRIDGE_H */