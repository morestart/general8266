#include <Arduino.h>
// #include <ArduinoJson.h>
// #include <Ticker.h>
#include "wifi.h"
#include "mqtt.h"
#include "definitions.h"
#include "button.h"


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