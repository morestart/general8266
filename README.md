# ESP8266

## 结构

```
----general8266
    |----tree.py
    |----LICENSE
    |----test
    |    |----README
    |----include
    |    |----wifi.h
    |    |----processdata.h
    |    |----README
    |    |----mqtt.h
    |    |----button.h
    |    |----definitions.h
    |----platformio.ini
    |----README.md
    |----lib
    |    |----README
    |----src
    |    |----mqtt.cpp
    |    |----button.cpp
    |    |----processData.cpp
    |    |----wifi.cpp
    |    |----main.cpp
```

## 依赖树

```
|-- <ArduinoJson> 6.11.5
|-- <ESP8266WebServer> 1.0
|   |-- <ESP8266WiFi> 1.0
|-- <ESP8266WiFi> 1.0
|-- <Ticker> 3.1.5
|-- <WifiManager> 0.14
|   |-- <DNSServer> 1.1.1
|   |   |-- <ESP8266WiFi> 1.0
|   |-- <ESP8266WebServer> 1.0
|   |   |-- <ESP8266WiFi> 1.0
|   |-- <ESP8266WiFi> 1.0
|-- <PubSubClient> 2.7 
```

## 代码说明

```c
void setup()
{
	Serial.begin(115200);
    // 初始化重置按钮
	initButton();
    // 加载web配置
	loadWifiWebConfig();
    // 加载mqtt配置
	loadMQTTConfig();
    // 初始化定时器
	initTimer();
    // 订阅主题
	subscribeTopic_();
	pinMode(D4, OUTPUT);
}

void loop()
{
    // 保持mqtt连接
	keepMqttConnect();
    // 检测是否重置wifi mqtt信息
	getButtonDown();
    // 更新定时器
	loopTimer();
}
```

> 请勿随意修改主函数中引用的函数

初始波特率115200, 初始化重置按钮,第一次上电加载web配置页面配置wifi以及mqtt的信息,然后加载本地mqtt信息

循环中用于检测mqtt是否掉线,如果掉线开始重连重订阅,以及检测按钮是否按下,按下的话就执行清空信息操作.

在本项目中,只需要关注processData这个文件即可,此文件包含mqtt消息以及定时任务的处理和初始化,在这个文件中
处理你的业务逻辑,`void subscribeTopic_()`中订阅主题(在这个函数中订阅的主题可以自动重订阅),然后使用
定时函数持续发布消息
