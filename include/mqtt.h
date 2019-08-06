#ifndef _MQTT_H
#define _MQTT_H

void loadConfig();
void connectMqtt(char server[], char name[], char password[], char port[]);
void reconnect();
void publishMessage(const char topic[],const char data[]);
void subscribeTopic(const char topic[]);
int keepMqttConnect();


#endif