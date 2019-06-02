#include <WS2812FX.h>
#include <ArduinoJson.h>
#include "light.h"
#include "mqtt.h"
#include "definitions.h"

int LED_NUM = 100;
int LED_PIN = D5;

WS2812FX ws2812fx = WS2812FX(LED_NUM, LED_PIN, NEO_GRB + NEO_KHZ800);
// extern char availability_topic[200];
// extern char command_topic[200];
// extern char state_topic[200];


// 初始化灯带
void setWs2812()
{
    ws2812fx.init();
    ws2812fx.setBrightness(0);
    ws2812fx.setSpeed(25);
    ws2812fx.start();
}

void startService() {
    ws2812fx.service();
}

// 打开灯带
void openWs2812()
{
    ws2812fx.setBrightness(255);
    ws2812fx.setMode(0);
    ws2812fx.setColor(255, 255, 255);
}

// 关闭灯带
void closeWs2812() { ws2812fx.setBrightness(0); }

// 设置亮度
void setWs2812Brightness(int bri) { ws2812fx.setBrightness(bri); }

// 设置颜色
void setRgbColor(int r, int g, int b) { ws2812fx.setColor(r, g, b); }

// 设置模式
void setMode(const char *mode)
{
    if (strcmp(mode, "STATIC") == 0)
    {
        ws2812fx.setMode(STATIC);
    }
    else if (strcmp(mode, "BLINK") == 0)
    {
        ws2812fx.setMode(BLINK);
    }
    else if (strcmp(mode, "BREATH") == 0)
    {
        ws2812fx.setMode(BREATH);
    }
    else if (strcmp(mode, "COLOR_WIPE") == 0)
    {
        ws2812fx.setMode(COLOR_WIPE);
    }
    else if (strcmp(mode, "COLOR_WIPE_INV") == 0)
    {
        ws2812fx.setMode(COLOR_WIPE_INV);
    }
    else if (strcmp(mode, "COLOR_WIPE_REV") == 0)
    {
        ws2812fx.setMode(COLOR_WIPE_REV);
    }
    else if (strcmp(mode, "COLOR_WIPE_REV_INV") == 0)
    {
        ws2812fx.setMode(COLOR_WIPE_REV_INV);
    }
    else if (strcmp(mode, "COLOR_WIPE_RANDOM") == 0)
    {
        ws2812fx.setMode(COLOR_WIPE_RANDOM);
    }
    else if (strcmp(mode, "RANDOM_COLOR") == 0)
    {
        ws2812fx.setMode(RANDOM_COLOR);
    }
    else if (strcmp(mode, "SINGLE_DYNAMIC") == 0)
    {
        ws2812fx.setMode(SINGLE_DYNAMIC);
    }
    else if (strcmp(mode, "MULTI_DYNAMIC") == 0)
    {
        ws2812fx.setMode(MULTI_DYNAMIC);
    }
    else if (strcmp(mode, "RAINBOW") == 0)
    {
        ws2812fx.setMode(RAINBOW);
    }
    else if (strcmp(mode, "RAINBOW_CYCLE") == 0)
    {
        ws2812fx.setMode(RAINBOW_CYCLE);
    }
    else if (strcmp(mode, "BLINK") == 0)
    {
        ws2812fx.setMode(BLINK);
    }
    else if (strcmp(mode, "SCAN") == 0)
    {
        ws2812fx.setMode(SCAN);
    }
    else if (strcmp(mode, "DUAL_SCAN") == 0)
    {
        ws2812fx.setMode(DUAL_SCAN);
    }
    else if (strcmp(mode, "FADE") == 0)
    {
        ws2812fx.setMode(FADE);
    }
    else if (strcmp(mode, "THEATER_CHASE") == 0)
    {
        ws2812fx.setMode(THEATER_CHASE);
    }
    else if (strcmp(mode, "THEATER_CHASE_RAINBOW") == 0)
    {
        ws2812fx.setMode(THEATER_CHASE_RAINBOW);
    }
    else if (strcmp(mode, "RUNNING_LIGHTS") == 0)
    {
        ws2812fx.setMode(RUNNING_LIGHTS);
    }
    else if (strcmp(mode, "TWINKLE") == 0)
    {
        ws2812fx.setMode(TWINKLE);
    }
    else if (strcmp(mode, "TWINKLE_RANDOM") == 0)
    {
        ws2812fx.setMode(TWINKLE_RANDOM);
    }
    else if (strcmp(mode, "TWINKLE_FADE") == 0)
    {
        ws2812fx.setMode(TWINKLE_FADE);
    }
    else if (strcmp(mode, "TWINKLE_FADE_RANDOM") == 0)
    {
        ws2812fx.setMode(TWINKLE_FADE_RANDOM);
    }
    else if (strcmp(mode, "SPARKLE") == 0)
    {
        ws2812fx.setMode(SPARKLE);
    }
    else if (strcmp(mode, "FLASH_SPARKLE") == 0)
    {
        ws2812fx.setMode(FLASH_SPARKLE);
    }
    else if (strcmp(mode, "HYPER_SPARKLE") == 0)
    {
        ws2812fx.setMode(HYPER_SPARKLE);
    }
    else if (strcmp(mode, "STROBE") == 0)
    {
        ws2812fx.setMode(STROBE);
    }
    else if (strcmp(mode, "STROBE_RAINBOW") == 0)
    {
        ws2812fx.setMode(STROBE_RAINBOW);
    }
    else if (strcmp(mode, "MULTI_STROBE") == 0)
    {
        ws2812fx.setMode(MULTI_STROBE);
    }
    else if (strcmp(mode, "BLINK_RAINBOW") == 0)
    {
        ws2812fx.setMode(BLINK_RAINBOW);
    }
    else if (strcmp(mode, "CHASE_WHITE") == 0)
    {
        ws2812fx.setMode(CHASE_WHITE);
    }
    else if (strcmp(mode, "CHASE_COLOR") == 0)
    {
        ws2812fx.setMode(CHASE_COLOR);
    }
    else if (strcmp(mode, "CHASE_RANDOM") == 0)
    {
        ws2812fx.setMode(CHASE_RANDOM);
    }
    else if (strcmp(mode, "CHASE_RAINBOW") == 0)
    {
        ws2812fx.setMode(CHASE_RAINBOW);
    }
    else if (strcmp(mode, "CHASE_FLASH") == 0)
    {
        ws2812fx.setMode(CHASE_FLASH);
    }
    else if (strcmp(mode, "CHASE_FLASH_RANDOM") == 0)
    {
        ws2812fx.setMode(CHASE_FLASH_RANDOM);
    }
    else if (strcmp(mode, "CHASE_RAINBOW_WHITE") == 0)
    {
        ws2812fx.setMode(CHASE_RAINBOW_WHITE);
    }
    else if (strcmp(mode, "CHASE_BLACKOUT") == 0)
    {
        ws2812fx.setMode(CHASE_BLACKOUT);
    }
    else if (strcmp(mode, "CHASE_BLACKOUT_RAINBOW") == 0)
    {
        ws2812fx.setMode(CHASE_BLACKOUT_RAINBOW);
    }
    else if (strcmp(mode, "COLOR_SWEEP_RANDOM") == 0)
    {
        ws2812fx.setMode(COLOR_SWEEP_RANDOM);
    }
    else if (strcmp(mode, "RUNNING_COLOR") == 0)
    {
        ws2812fx.setMode(RUNNING_COLOR);
    }
    else if (strcmp(mode, "RUNNING_RED_BLUE") == 0)
    {
        ws2812fx.setMode(RUNNING_RED_BLUE);
    }
    else if (strcmp(mode, "RUNNING_RANDOM") == 0)
    {
        ws2812fx.setMode(RUNNING_RANDOM);
    }
    else if (strcmp(mode, "LARSON_SCANNER") == 0)
    {
        ws2812fx.setMode(LARSON_SCANNER);
    }
    else if (strcmp(mode, "COMET") == 0)
    {
        ws2812fx.setMode(COMET);
    }
    else if (strcmp(mode, "FIREWORKS") == 0)
    {
        ws2812fx.setMode(FIREWORKS);
    }
    else if (strcmp(mode, "FIREWORKS_RANDOM") == 0)
    {
        ws2812fx.setMode(FIREWORKS_RANDOM);
    }
    else if (strcmp(mode, "MERRY_CHRISTMAS") == 0)
    {
        ws2812fx.setMode(MERRY_CHRISTMAS);
    }
    else if (strcmp(mode, "FIRE_FLICKER") == 0)
    {
        ws2812fx.setMode(FIRE_FLICKER);
    }
    else if (strcmp(mode, "FIRE_FLICKER_SOFT") == 0)
    {
        ws2812fx.setMode(FIRE_FLICKER_SOFT);
    }
    else if (strcmp(mode, "FIRE_FLICKER_INTENSE") == 0)
    {
        ws2812fx.setMode(FIRE_FLICKER_INTENSE);
    }
    else if (strcmp(mode, "CIRCUS_COMBUSTUS") == 0)
    {
        ws2812fx.setMode(CIRCUS_COMBUSTUS);
    }
    else if (strcmp(mode, "HALLOWEEN") == 0)
    {
        ws2812fx.setMode(HALLOWEEN);
    }
    else if (strcmp(mode, "BICOLOR_CHASE") == 0)
    {
        ws2812fx.setMode(BICOLOR_CHASE);
    }
    else if (strcmp(mode, "TRICOLOR_CHASE") == 0)
    {
        ws2812fx.setMode(TRICOLOR_CHASE);
    }
}

void processWs2812Data(char data[]) {
    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, data);
    
    if (!error) {
        const char *state = doc["state"];
        const char *effect = doc["effect"];
        const int8_t brightness = doc["brightness"];
        const int8_t r = doc["color"]["r"];
        const int8_t g = doc["color"]["g"];
        const int8_t b = doc["color"]["b"];


        Serial.println(state);
        Serial.println(brightness);
        Serial.println(r);
        Serial.println(g);
        Serial.println(b);
        Serial.println("------------");


        // 开
        if ((r == NULL && g == NULL && b == NULL && brightness == NULL) &&
            (effect == NULL && strcmp(state, "ON") == 0))
        {
            openWs2812();

            publishMessage(state_topic, "{\"state\":\"ON\"}");
            // 关
        }
        else if ((strcmp(state, "OFF") == 0) &&
                (r == NULL && g == NULL && b == NULL && effect == NULL &&
                brightness == NULL))
        {
            closeWs2812();
            publishMessage(state_topic, "{\"state\":\"OFF\"}");
        }

        // 调亮度
        if ((strcmp(state, "ON") == 0) && (brightness != NULL))
        {   Serial.println("调亮度");
            setWs2812Brightness(brightness);
        }

        // 调特效
        if ((strcmp(state, "ON") == 0) && (effect != NULL))
        {
            setMode(effect);
        }

        // 调颜色
        if ((strcmp(state, "ON") == 0) && (r != NULL || g != NULL || b != NULL))
        {
            setRgbColor(r, g, b);
        }
    }
}