#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
int getSensorData();
void dhtSetup();
float getHum();
float getTem();

#endif