#include "patterns.hpp"
#include "Arduino.h"
void solid(CRGB leds[], uint8_t hue, uint8_t saturation, uint8_t brightness, int pixels)
{
    CHSV color = CHSV(hue,saturation,brightness);
    fill_solid(leds,pixels,color);
}

void rainbowfade(CRGB leds[], uint8_t saturation, uint8_t brightness, int tickms, int pixels)
{
    uint8_t hue = ((millis() / tickms) % 256);
    CHSV color = CHSV(hue,saturation,brightness);
    fill_solid(leds,pixels,color);
    FastLED.show();
}

void brightfade(CRGB leds[], uint8_t hue, uint8_t saturation, uint8_t brightness1, uint8_t brightness2, int tickms,int pixels)
{
    uint8_t brightness = map(((millis() / tickms) % 256),0,255,brightness1,brightness2);
    CHSV color = CHSV(hue,saturation,brightness);
    fill_solid(leds,pixels,color);
    FastLED.show();
}

void huefade(CRGB leds[], uint8_t hue1, uint8_t hue2, uint8_t saturation, uint8_t brightness, int tickms,int pixels)
{
    uint8_t hue =  map(((millis() / tickms) % 256),0,255,hue1,hue2);
    CHSV color = CHSV(hue,saturation,brightness);
    fill_solid(leds,pixels,color);
    FastLED.show();
}

void rainbowbreathe(CRGB leds[], uint8_t saturation, uint8_t brightness, int bpm, int pixels)
{
    uint8_t hue =  beatsin8(bpm, 0,255, 0,0);
    CHSV color = CHSV(hue,saturation,brightness);
    fill_solid(leds,pixels,color);
    FastLED.show();
}
void brightbreathe(CRGB leds[], uint8_t hue, uint8_t saturation, uint8_t brightness1, uint8_t brightness2, int bpm,int pixels)
{
    uint8_t brightness =  beatsin8(bpm,brightness1, brightness2, 0,0);
    CHSV color = CHSV(hue,saturation,brightness);
    fill_solid(leds,pixels,color);
    FastLED.show();
}
void huebreathe(CRGB leds[], uint8_t hue1, uint8_t hue2, uint8_t saturation, uint8_t brightness, int bpm,int pixels)
{
    uint8_t hue =  beatsin8(bpm, hue1, hue2, 0,0);
    CHSV color = CHSV(hue,saturation,brightness);
    fill_solid(leds,pixels,color);
    FastLED.show();
}