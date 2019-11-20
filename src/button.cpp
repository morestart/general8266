#include <Arduino.h>
#include "wifi.h"
#include "definitions.h"

int pinInterrupt = 0;
int count = 0;

void initButton()
{
  pinMode(pinInterrupt, INPUT);
}

void getButtonDown()
{
  while (digitalRead(pinInterrupt) == LOW)
  {
    delay(200);
    count++;
    if (count >= 10)
    { //>=5s
      #if LOG
        Serial.println("Long Key");
        clean();
        ESP.restart();
        break;
      #endif
    }
  }
  count = 0;
  delay(200);
}