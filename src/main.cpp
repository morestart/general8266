#include <Arduino.h>
#include "wifi.h"
#include "mqtt.h"
#include "definitions.h"
#include <DHTesp.h>
#include <ArduinoJson.h>
#include <Ticker.h>


void dhtData();

char data[40];

DHTesp dht;

// 创建定时器
Ticker publishDhtData(dhtData, 5000);

void dhtData() {
  publishMessage("dht", data);
}

void setup() {
  // 开启定时器
  publishDhtData.start();
  Serial.begin(115200);
  // clean();
  
  loadWifiWebConfig();
  loadConfig();
  dht.setup(D3, DHTesp::DHT11);
}

void loop() {
  // 更新定时器
  publishDhtData.update();

  int code = keepMqttConnect();
  
  if (code == 1) {
    Serial.println("re subscribe");
    subscribeTopic(command_topic);
  }
  int hum = dht.getHumidity();
  int tem = dht.getTemperature();
  
  StaticJsonDocument<200> doc;
  doc["temperature"] = tem;
  doc["humidity"] = hum;
  
  serializeJson(doc, data);
}