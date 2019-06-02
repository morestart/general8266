#ifndef _MQTT_H
#define _MQTT_H

extern void loadConfig();
extern void connectMqtt(char server[], char name[], char password[], char port[]);
extern void reconnect();
extern void publishMessage(char topic[], char data[]);
extern void subscribeTopic(char topic[]);
extern int keepMqttConnect();


#endif