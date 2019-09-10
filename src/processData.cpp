#include <Arduino.h>
#include "mqtt.h"
#include "Ticker.h"


void publishTopic_();

Ticker time1(publishTopic_, 1000);

void initTimer() {
    time1.start();
}

// 在这里加入需要的定时器,这个函数会在主函数内一直运行更新定时器
void loopTimer() {
    time1.update();
}

void publishTopic_() {
    // 在这里发布主题
}

void subscribeTopic_() {
    // 在这里订阅主题
}

void processData(const char* topic, const char* data)
{
    // 数据处理
    Serial.println(data);
    Serial.println(topic);
}