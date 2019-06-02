#ifndef _LIGHT_H
#define _LIGHT_H

extern void setWs2812();
extern void openWs2812();
extern void closeWs2812();
extern void setWs2812Brightness(int bri);
extern void setRgbColor(int r, int g, int b);
extern void setMode(const char *mode);
extern void startService();
// extern void subscribe_light();
// extern void publish_light();
extern void processWs2812Data(char data[]);


// TODO: 将引脚和灯珠数变为可配置
// #define LED_NUM 300
// #define LED_PIN D5


#define STATIC 0
#define BLINK 1
#define BREATH 2
#define COLOR_WIPE 3
#define COLOR_WIPE_INV 4
#define COLOR_WIPE_REV 5
#define COLOR_WIPE_REV_INV 6
#define COLOR_WIPE_RANDOM 7
#define RANDOM_COLOR 8
#define SINGLE_DYNAMIC 9
#define MULTI_DYNAMIC 10
#define RAINBOW 11
#define RAINBOW_CYCLE 12
#define SCAN 13
#define DUAL_SCAN 14
#define FADE 15
#define THEATER_CHASE 16
#define THEATER_CHASE_RAINBOW 17
#define RUNNING_LIGHTS 18
#define TWINKLE 19
#define TWINKLE_RANDOM 20
#define TWINKLE_FADE 21
#define TWINKLE_FADE_RANDOM 22
#define SPARKLE 23
#define FLASH_SPARKLE 24
#define HYPER_SPARKLE 25
#define STROBE 26
#define STROBE_RAINBOW 27
#define MULTI_STROBE 28
#define BLINK_RAINBOW 29
#define CHASE_WHITE 30
#define CHASE_COLOR 31
#define CHASE_RANDOM 32
#define CHASE_RAINBOW 33
#define CHASE_FLASH 34
#define CHASE_FLASH_RANDOM 35
#define CHASE_RAINBOW_WHITE 36
#define CHASE_BLACKOUT 37
#define CHASE_BLACKOUT_RAINBOW 38
#define COLOR_SWEEP_RANDOM 39
#define RUNNING_COLOR 40
#define RUNNING_RED_BLUE 41
#define RUNNING_RANDOM 42
#define LARSON_SCANNER 43
#define COMET 44
#define FIREWORKS 45
#define FIREWORKS_RANDOM 46
#define MERRY_CHRISTMAS 47
#define FIRE_FLICKER 48
#define FIRE_FLICKER_SOFT 49
#define FIRE_FLICKER_INTENSE 50
#define CIRCUS_COMBUSTUS 51
#define HALLOWEEN 52
#define BICOLOR_CHASE 53
#define TRICOLOR_CHASE 54
#define ICU 55

#endif
