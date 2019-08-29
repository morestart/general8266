#include <Arduino.h>
#include "mqtt.h"

void processData(const char* data)
{
    Serial.println(data);
    publishMessage("ok", "hello");
}