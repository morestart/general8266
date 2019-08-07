#include <Arduino.h>
#include "mqtt.h"

void processData(const char* data)
{
    publishMessage("ok", "hello");
}