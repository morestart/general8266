#include <Arduino.h>
#include "mqtt.h"
#include "Ticker.h"


void publishTopic_();

Ticker time1(publishTopic_, 1000);

void initTimer() {
    time1.start();
}

void loopTimer() {
    time1.update();
}

void publishTopic_() {
    publishMessage("home/bedroom/switch1/available", "online");
}

void subscribeTopic_() {
    subscribeTopic("home/bedroom/switch1/set");
}

void processData(const char* topic, const char* data)
{
    Serial.println(data);
    Serial.println(topic);
    if (strcmp(topic, "home/bedroom/switch1/set") == 0) {
        if (strcmp(data, "ON") == 0)
        {
            digitalWrite(D4, LOW);
            publishMessage("home/bedroom/switch1", "ON");
        } 
        else if (strcmp(data, "OFF") == 0)
        {
            digitalWrite(D4, HIGH);
            publishMessage("home/bedroom/switch1", "OFF");
        }
    }
    else {
        Serial.println("NO topic match");
    }
}
