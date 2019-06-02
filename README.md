# ESP8266

## RGB

```c
#include <Arduino.h>
#include "wifi.h"
#include "mqtt.h"


unsigned long previousMillis = 0;
const long interval = 5000;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // clean();
  
  loadWifiWebConfig();
  loadConfig();

  subscribeTopic("L/rgb/set");
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
  
  int code = keepMqttConnect();
  
  if (code == 1) {
    Serial.println("re subscribe");
    subscribeTopic("L/rgb/set");
  }

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    publishMessage("LAvailability", "online");
  }
}
```

> 如果需要处理来自mqtt的数据,参考mqtt.cpp文件中的 TODO,根据不同主题进入不同的消息处理函数
