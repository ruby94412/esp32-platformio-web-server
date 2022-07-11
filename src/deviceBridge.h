#ifndef DEVICEBRIDGE_H /* include guards */
#define DEVICEBRIDGE_H

/* blinky initialization function */
void startModbus();
void modbusInLoop();
extern String temperature;

#endif /* DEVICEBRIDGE_H */