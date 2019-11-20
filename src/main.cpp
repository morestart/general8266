#include <Arduino.h>
#include "wifi.h"
#include "mqtt.h"
#include "definitions.h"
#include "button.h"
#include "processdata.h"
#include "sensor.h"


void setup()
{
	Serial.begin(9600);
	// clean();
	initButton();
	dhtSetup();
	loadWifiWebConfig();
	loadMQTTConfig();
	initTimer();
	subscribeTopic_();
}

void loop()
{
	keepMqttConnect();
	getButtonDown();
	loopTimer();
}