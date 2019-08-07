# ESP8266

## 结构

```
----general8266
    |----include
    |    |----button.h
    |    |----definitions.h
    |    |----mqtt.h
    |    |----README
    |    |----wifi.h
    |----lib
    |    |----README
    |----LICENSE
    |----platformio.ini
    |----README.md
    |----src
    |    |----button.cpp
    |    |----main.cpp
    |    |----mqtt.cpp
    |    |----wifi.cpp
    |----test
    |    |----README
    |----tree.py
```

## 代码说明

```c
void setup()
{
	Serial.begin(115200);
	initButton();
	loadWifiWebConfig();
	loadMQTTConfig();
}

void loop()
{
	keepMqttConnect();
	getButtonDown();
}
```

初始波特率115200, 初始化重置按钮,第一次上电加载web配置页面配置wifi以及mqtt的信息,然后加载本地mqtt信息

循环中用于检测mqtt是否掉线,如果掉线开始重连重订阅,以及检测按钮是否按下,按下的话就执行清空信息操作.

在项目中,只需要使用两个函数即
```c
void publishMessage(const char topic[],const char data[]);
void subscribeTopic(const char topic[]);
```
一个是发布信息,一个是订阅主题.

只需要关心的就是processData.cpp这个文件,这个文件用于处理业务逻辑,从mqtt broker传来的数据会传入此文件中的处理函数中,
你只需要扩展这个函数就可以实现你自己的业务逻辑