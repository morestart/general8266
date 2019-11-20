#include <Arduino.h>
#include <DHTesp.h>


DHTesp dht;
int DHTPin = D6;

const int getCo2Order[] = {0x42, 0x4D, 0xE3, 0x00, 0x00, 0x01, 0x72};
char sensorData[10];

int co2 = 0;

void dhtSetup() {
  dht.setup(DHTPin, DHTesp::DHT11);
}

float getHum() {
  delay(dht.getMinimumSamplingPeriod());
  float hum = dht.getHumidity();
  return hum;
}

float getTem() {
  delay(dht.getMinimumSamplingPeriod());
  float tem = dht.getTemperature();
  return tem;
}

int getSensorData() {
    
  for (int i = 0; i < 7; i++)
  {
      Serial.write(getCo2Order[i]);
  }

  if (Serial.available())
  {
      if (Serial.read() == 0x42)
      {
          if (Serial.read() == 0x4d)
          {
              Serial.readBytes(sensorData, 10);
              co2 = (sensorData[2]*256) + sensorData[3];
              return co2;
          }  
      }
  }
  // 返回为400则无数据
  return 400;
}