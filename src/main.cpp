#include <Arduino.h>
// #include <ArduinoJson.h>
#include <Ticker.h>
#include "wifi.h"
#include "mqtt.h"
#include "definitions.h"
#include "button.h"


// 创建定时器
// Ticker flashSPIFSData(getButtonDown, 100);

// char data[20];

void setup()
{
	
	Serial.begin(115200);
	initButton();
	// 开启定时器
	// flashSPIFSData.start();
	// clean();
	loadWifiWebConfig();
	loadConfig();
}

void loop()
{
	// 更新定时器
	// flashSPIFSData.update();

	int code = keepMqttConnect();

	if (code == 1)
	{
		Serial.println("re subscribe");
		subscribeTopic(command_topic);
	}

	getButtonDown();
	// StaticJsonDocument<200> doc;
	// doc["temperature"] = 10;
	// doc["humidity"] = 20;

	// serializeJson(doc, data);
}