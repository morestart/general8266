#include <ArduinoJson.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <FS.h>
#include <Arduino.h>
#include "definitions.h"
#include "processdata.h"

void loadConfig();
void callback(char *topic, byte *payload, int length);
void connectMqtt(char server[], char name[], char password[], char port[]);
void reconnect();
void keepMqttConnect();
void subscribeTopic(const char topic[]);
void publishMessage();

char mqttUser[30];
char mqttPassword[30];
char mqttServer[20];
char mqttPort[10];

WiFiClient espClient;
PubSubClient client(espClient);

void loadMQTTConfig()
{
  if (SPIFFS.begin())
  {
#if LOG
    Serial.println("mounted file system");
#endif
    if (SPIFFS.exists("/config.json"))
    {
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile)
      {
#if LOG
        Serial.println("opened config file");
#endif
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);

        DynamicJsonDocument json(1024);
        DeserializationError error = deserializeJson(json, buf.get());
        serializeJson(json, Serial);
        if (!error)
        {
#if LOG
          Serial.println("\nparsed json");
#endif

          strcpy(mqttServer, json["mqtt_server"]);
          strcpy(mqttPort, json["mqtt_port"]);
          strcpy(mqttUser, json["mqtt_user_name"]);
          strcpy(mqttPassword, json["mqtt_password"]);

          //连接mqtt
          connectMqtt(mqttServer, mqttUser, mqttPassword, mqttPort);
        }
        else
        {
#if LOG
          Serial.println("failed to load json config");
#endif
        }
      }
    }
    else
    {
#if LOG
      Serial.println("no file");
#endif
      SPIFFS.format();
      ESP.restart();
    }
  }
  else
  {
#if LOG
    Serial.println("failed to mount FS");
#endif
  }
}

void callback(char *topic, byte *payload, int length)
{
  int i;
#if LOG
  Serial.print("Message in topic: ");
  Serial.println(topic);
  Serial.println();
#endif
  char receivedChar[1024];
  for (i = 0; i < length; i++)
  {
    receivedChar[i] = (char)payload[i];
  }
  // 字符串末尾记得加 \0嗷
  receivedChar[i] = '\0';
#if LOG
  Serial.print("message: ");
  Serial.println(receivedChar);
#endif

  processData(topic, receivedChar);
}

void connectMqtt(char server[], char name[], char password[], char port[])
{
  int _port = atoi(port);

  client.setServer(server, _port);
  client.setCallback(callback);

  // 上线订阅主题
  while (!client.connected())
  {
#if LOG
    Serial.println("Connecting to MQTT...");
#endif
    // 将连接mqtt的ID替换为chip id,防止冲突导致下线
    char ID[20];
    ltoa(ESP.getChipId(), ID, 10);

    if (client.connect(ID, name, password))
    {
#if LOG
      Serial.println("connected");
#endif
    }
    else
    {
#if LOG
      Serial.println("Failed state");
      Serial.println(client.state());
#endif
      delay(2000);
    }
  }
}

void reconnect()
{
  // keep the cycle until esp8266 connected the mqtt server
  while (!client.connected())
  {
#if LOG
    Serial.print("Attempting MQTT connection...");
#endif
    // Attempt to connect
    char ID[20];
    ltoa(ESP.getChipId(), ID, 10);

    if (client.connect(ID, mqttUser, mqttPassword))
    {
#if LOG
      Serial.println("re connected");
#endif

      subscribeTopic_();
    }
    else
    {
#if LOG
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
#endif
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void keepMqttConnect()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
}

void publishMessage(const char topic[], const char data[])
{
  client.publish(topic, data);
}

void subscribeTopic(const char topic[])
{
  client.subscribe(topic);
}