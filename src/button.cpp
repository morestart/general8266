#include <Arduino.h>
#include "wifi.h"

int pinInterrupt = 0;
int count = 0;

void initButton()
{
    pinMode(pinInterrupt, INPUT);
}

void getButtonDown()
{
    while(digitalRead(pinInterrupt) == LOW) {
        delay(200);
        count ++;
        if (count >= 25) { //>=5s
            Serial.println("Long Key"); 
            clean();
            ESP.restart();
            break;
        }
      }
    count = 0;
    delay(200);
}