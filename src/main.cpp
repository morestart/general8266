#include <Arduino.h>
#include "wifi.h"
#include "mqtt.h"
#include "definitions.h"
#include "button.h"
#include "processdata.h"


void setup()
{
	Serial.begin(115200);
	// clean();
	initButton();
	loadWifiWebConfig();
	loadMQTTConfig();
	// initTimer();
	subscribeTopic_();
}
void loop()
{
	keepMqttConnect();
	getButtonDown();
}