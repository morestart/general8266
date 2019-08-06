#include <Arduino.h>
// #include <ArduinoJson.h>
#include <Ticker.h>
#include "wifi.h"
#include "mqtt.h"
#include "definitions.h"
#include "button.h"


void setup()
{
	
	Serial.begin(115200);
	initButton();
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
}