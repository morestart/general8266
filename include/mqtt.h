#ifndef _MQTT_H
#define _MQTT_H

void loadMQTTConfig();
void connectMqtt(char server[], char name[], char password[], char port[]);
void reconnect();
void publishMessage(const char topic[],const char data[]);
void subscribeTopic(const char topic[]);
void keepMqttConnect();
void offlineResubscribe();

#endif