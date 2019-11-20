#include <Arduino.h>
#include <ArduinoJson.h>
#include "mqtt.h"
#include "Ticker.h"
#include "sensor.h"

void publishTopic_();
void heart();

Ticker time1(publishTopic_, 60000);
Ticker time2(heart, 1000);

void initTimer()
{
    time1.start();
    time2.start();
}

// 在这里加入需要的定时器,这个函数会在主函数内一直运行更新定时器
void loopTimer()
{
    time1.update();
    time2.update();
}

void heart()
{
    publishMessage("classroomSensor/available", "online");
}

void publishTopic_()
{
    // 在这里发布主题
    int co2 = getSensorData();
    float hum = getHum();
    delay(200);
    float tem = getTem();

    DynamicJsonDocument doc(1024);
    if (isnan(hum)) {
        hum = 0;
    }
    if (isnan(tem))
    {
        tem = 0;
    }
    
    if (co2)
    {
        char data[100];
        doc["co2"] = co2;
        doc["hum"] = hum;
        doc["tem"] = tem;
        serializeJson(doc, data);
        publishMessage("classroomSensorData", data);
    }
}

void subscribeTopic_()
{
    // 在这里订阅主题
}

void processData(const char *topic, const char *data)
{
}