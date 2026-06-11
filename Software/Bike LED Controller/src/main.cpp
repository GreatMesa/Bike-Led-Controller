#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <FastLED.h>
#include "patterns.hpp"
#include "ina236.h"
#include "tmp117.h"


// How many leds in your strip?
#define NUM_LEDS 300
#define SERVICE_UUID "9648cccb-9798-46d5-8862-cf77ef5b3585"
#define CHARACTERISTIC_UUID "d87a1cc7-8d4d-47c3-a5c3-0c06e6df6fba"
// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 27

int brightness = 255;
int saturation = 255;
// Define the array of leds
CRGB leds[NUM_LEDS];
ina236 ina;
tmp117 tmp;

void setup() { 
    // Uncomment/edit one of the following lines for your leds arrangement.
    // ## Clockless types ##
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is assumed
    Wire.begin();
    Serial.begin(115200);

    BLEDevice::init("LED Controller");
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(SERVICE_UUID);
    BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                     CHARACTERISTIC_UUID,
                                     BLECharacteristic::PROPERTY_READ |
                                     BLECharacteristic::PROPERTY_WRITE
                                     );
    pCharacteristic->setValue("Hello World says Neil");
    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->start();
    // Print log
    Serial.println(ina.initialize().c_str());
    Serial.println(tmp.initialize().c_str());
}
CHSV hue1 = CHSV(0,saturation,brightness);
CHSV hue2 = CHSV(200,saturation,brightness);
void loop() { 
  // fadebright(leds, 100, 255, dim8_video(0), dim8_video(200), 10,NUM_LEDS);  
  // fadehue(leds,15,160,255,dim8_video(200),10,NUM_LEDS);
  // rainbowfade(leds, saturation, brightness, 15, NUM_LEDS);
    rainbowbreathe(leds,255,100,10,NUM_LEDS);
  delay(10);
}

