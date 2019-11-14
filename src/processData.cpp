#include <Arduino.h>
#include "mqtt.h"
#include "Ticker.h"


void publishTopic_();

// 可以建立多个定时器 进行发布消息
Ticker time1(publishTopic_, 1000);

void publishTopic_() {
    publishMessage("home/bedroom/switch1/available", "online");
}

// 建立多个定时器的例子
/* 
Ticker time1(publishTopic_, 1000);
Ticker time2(publishhahaha, 1000);

void publishTopic_(){}
void publishhahaha(){}

void initTimer() {
    time1.start();
    time2.start();
}


void loopTimer() {
    time1.update();
    time2.update();
}
*/



// setup中调用,用于初始化定时器
void initTimer() {
    time1.start();
}

// 所有的定时器放在这里,这里会在主函数中调用,如果不需要定时器,需要删除main里面的调用
void loopTimer() {
    time1.update();
}



// 所有需要订阅的主题都放在这个函数里,这个函数会在mqtt.cpp里调用
void subscribeTopic_() {
    subscribeTopic("home/bedroom/switch1/set");
}

// 所有从mqtt来的消息都会经过这个函数 topic是订阅的主题,data是对应主题的数据
void processData(const char* topic, const char* data)
{
    Serial.println(data);
    Serial.println(topic);
    // 下面注释是一个开关的例子
    // if (strcmp(topic, "home/bedroom/switch1/set") == 0) {
    //     if (strcmp(data, "ON") == 0)
    //     {
    //         digitalWrite(D4, LOW);
    //         publishMessage("home/bedroom/switch1", "ON");
    //     } 
    //     else if (strcmp(data, "OFF") == 0)
    //     {
    //         digitalWrite(D4, HIGH);
    //         publishMessage("home/bedroom/switch1", "OFF");
    //     }
    // }
    // else {
    //     Serial.println("No topic match");
    // }
}
