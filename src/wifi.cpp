#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <WiFiManager.h>
#include "definitions.h"

// mqtt config info
char mqtt_user[30];
char mqtt_password[30];
char mqtt_server[20];
char mqtt_port[5] = "1883";

// save config flag, default is false
bool shouldSaveConfig = false;
WiFiManager wifiManager;

// clean SPIFS json data and reset wifi infomation
// this function will restart esp8266
void clean()
{
    wifiManager.resetSettings();
    SPIFFS.format();
    
}

// this function will set save flag to true
void saveConfigCallback()
{
    Serial.println("Should save config");
    shouldSaveConfig = true;
}

void loadWifiWebConfig()
{
    wifiManager.setSaveConfigCallback(saveConfigCallback);

    wifiManager.setTimeout(300);

    // add custom param
    WiFiManagerParameter custom_mqtt_server("server", "mqtt server", mqtt_server, 40);
    WiFiManagerParameter custom_mqtt_port("port", "mqtt port", mqtt_port, 6);
    WiFiManagerParameter custom_mqtt_usr("mqtt_user", "mqtt user name", mqtt_user, 40);
    WiFiManagerParameter custom_mqtt_password("mqtt_password", "mqtt password", mqtt_password, 40);

    WiFiManagerParameter custom_text("<p>MQTT Configuration</p>");
    wifiManager.addParameter(&custom_text);

    wifiManager.addParameter(&custom_mqtt_usr);
    wifiManager.addParameter(&custom_mqtt_password);
    wifiManager.addParameter(&custom_mqtt_server);
    wifiManager.addParameter(&custom_mqtt_port);

    if (!wifiManager.autoConnect(AP_NAME, AP_PASS))
    {
        Serial.println("Failed to connect and hit timeout");
        delay(3000);
        ESP.restart();
        delay(5000);
    }
    strcpy(mqtt_server, custom_mqtt_server.getValue());
    strcpy(mqtt_port, custom_mqtt_port.getValue());
    strcpy(mqtt_user, custom_mqtt_usr.getValue());
    strcpy(mqtt_password, custom_mqtt_password.getValue());

    if (shouldSaveConfig)
    {
        Serial.println("saving config");
        // TODO: 
        DynamicJsonDocument doc(1024);

        doc["mqtt_server"] = mqtt_server;
        doc["mqtt_port"] = mqtt_port;
        doc["mqtt_user_name"] = mqtt_user;
        doc["mqtt_password"] = mqtt_password;

        if (!SPIFFS.begin())
        {
            Serial.println("Failed to mount file system");
            return;
        }
        File configFile = SPIFFS.open("/config.json", "w");
        if (!configFile)
        {
            Serial.println("Failed to open config file for writing");
        }
        serializeJson(doc, Serial);
        serializeJson(doc, configFile);
        configFile.close();
    }
}