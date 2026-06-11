#include <FastLED.h>
#include <functional>
void solid(CRGB leds[], uint8_t h, uint8_t s, uint8_t b, int pixels);

void rainbowfade(CRGB leds[], uint8_t saturation, uint8_t brightness, int tickms, int pixels);

void brightfade(CRGB leds[], uint8_t hue, uint8_t saturation, uint8_t brightness1, uint8_t brightness2, int tickms,int pixels);

void huefade(CRGB leds[], uint8_t hue1, uint8_t hue2, uint8_t saturation, uint8_t brightness, int tickms,int pixels);

void rainbowbreathe(CRGB leds[], uint8_t saturation, uint8_t brightness, int bpm, int pixels);

void brightbreathe(CRGB leds[], uint8_t h, uint8_t s, uint8_t b1, uint8_t b2, int bpm,int pixels);

void huebreathe(CRGB leds[], uint8_t hue1, uint8_t hue2, uint8_t saturation, uint8_t brightness, int bpm,int pixels);


