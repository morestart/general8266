#include <ArduinoJson.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include <FS.h>
#include <Arduino.h>
#include "definitions.h"

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
        Serial.println("mounted file system");
        if (SPIFFS.exists("/config.json"))
        {

            // file exists, reading and loading
            Serial.println("reading config file");
            File configFile = SPIFFS.open("/config.json", "r");
            if (configFile)
            {
                Serial.println("opened config file");
                size_t size = configFile.size();
                // Allocate a buffer to store contents of the file.
                std::unique_ptr<char[]> buf(new char[size]);

                configFile.readBytes(buf.get(), size);
                // DynamicJsonBuffer jsonBuffer;
                // JsonObject &json = jsonBuffer.parseObject(buf.get());

                DynamicJsonDocument json(1024);
                DeserializationError error = deserializeJson(json, buf.get());
                serializeJson(json, Serial);
                if (!error)
                {
                    Serial.println("\nparsed json");

                    strcpy(mqttServer, json["mqtt_server"]);
                    strcpy(mqttPort, json["mqtt_port"]);
                    strcpy(mqttUser, json["mqtt_user_name"]);
                    strcpy(mqttPassword, json["mqtt_password"]);

                    //连接mqtt
                    connectMqtt(mqttServer, mqttUser, mqttPassword, mqttPort);
                }
                else
                {
                    Serial.println("failed to load json config");
                }
            }
        }
        else
        {
            Serial.println("no file");
            SPIFFS.format();
            ESP.restart();
        }
    }
    else
    {
        Serial.println("failed to mount FS");
    }
}

void callback(char *topic, byte *payload, int length)
{
    int i;
    Serial.print("Message in topic: ");
    Serial.println(topic);
    Serial.println();
    char receivedChar[100];
    for (i = 0; i < length; i++)
    {
        receivedChar[i] = (char)payload[i];
    }
    // 字符串末尾记得加 \0嗷
    receivedChar[i] = '\0';

    Serial.print("message: ");
    Serial.println(receivedChar);

    // TODO: 消息处理任务
    // if (strcmp(topic, command_topic) == 0) {
    //     processWs2812Data(receivedChar);
    // }
}

void connectMqtt(char server[], char name[], char password[], char port[])
{
    int _port = atoi(port);

    client.setServer(server, _port);
    client.setCallback(callback);

    // 上线订阅主题
    while (!client.connected())
    {
        Serial.println("Connecting to MQTT...");
        // 将连接mqtt的ID替换为chip id,防止冲突导致下线
        char ID[20];
        ltoa(ESP.getChipId(), ID, 10);

        if (client.connect(ID, name, password))
        {
            Serial.println("connected");
        }
        else
        {
            Serial.println("Failed state");
            Serial.println(client.state());
            delay(2000);
        }
    }
}

void reconnect()
{
    // keep the cycle until esp8266 connected the mqtt server
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        char ID[20];
        ltoa(ESP.getChipId(), ID, 10);

        if (client.connect(ID))
        {
            Serial.println("connected");
            // TODO:掉线重订阅
            subscribeTopic(command_topic);
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println("try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}


// TODO:但应用可以直接在此函数内重订阅
void keepMqttConnect()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();
}

// void offlineResubscribe() {
//     int code = keepMqttConnect();

// 	if (code == 1)
// 	{
// 		Serial.println("re subscribe");
// 		subscribeTopic(command_topic);
// 	}
// }

void publishMessage(const char topic[], const char data[])
{
    client.publish(topic, data);
}

void subscribeTopic(const char topic[])
{
    client.subscribe(topic);
}
