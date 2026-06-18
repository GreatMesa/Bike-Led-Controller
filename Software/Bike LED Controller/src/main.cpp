#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <FastLED.h>
#include "patterns.hpp"
#include "ina236.h"
#include "tmp117.h"
#include "bmi270.h"

// How many leds in your strip?
#define NUM_LEDS 300
#define SERVICE_UUID "9648cccb-9798-46d5-8862-cf77ef5b3585"
#define CHARACTERISTIC_UUID "d87a1cc7-8d4d-47c3-a5c3-0c06e6df6fba"

#define DATA_PIN 27

int brightness = 255;
int saturation = 255;
// Define the array of leds
CRGB leds[NUM_LEDS];
ina236 ina;
tmp117 tmp;

SemaphoreHandle_t i2cMutex;
void ina236Task(void *parameters)
{
  for (;;)
  {
    xSemaphoreTake(i2cMutex,portMAX_DELAY);
    ina.updateINA236();
    xSemaphoreGive(i2cMutex);
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

void tmp117Task(void *parameters)
{
  for (;;)
  {
    xSemaphoreTake(i2cMutex,portMAX_DELAY);
    tmp.getTemperature();
    xSemaphoreGive(i2cMutex);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void ledRender(void * parameters)
{
    for (;;)
  {
    rainbowbreathe(leds, 255,255,20,300);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void setup()
{
  // Uncomment/edit one of the following lines for your leds arrangement.
  // ## Clockless types ##
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS); // GRB ordering is assumed
  Wire.begin();
  Wire.setClock(100000);
  Wire.setTimeOut(10);
  Serial.begin(115200);


  ina.initialize();
  tmp.initialize();

  i2cMutex = xSemaphoreCreateMutex();
  BLEDevice::init("LED Controller");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE);
  pCharacteristic->setValue("Hello World says Neil");
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
  pService->start();
  
  xTaskCreatePinnedToCore(ina236Task, "INA236 Task", 4 * 1024, NULL, 1, NULL,1);
  xTaskCreatePinnedToCore(tmp117Task, "TMP117 Task", 4 * 1024, NULL, 1, NULL,1);
  xTaskCreatePinnedToCore(ledRender, "LED Render", 4 * 1024, NULL, 1, NULL,1);
}
CHSV hue1 = CHSV(0, saturation, brightness);
CHSV hue2 = CHSV(200, saturation, brightness);
void loop()
{
  // fadebright(leds, 100, 255, dim8_video(0), dim8_video(200), 10,NUM_LEDS);
  // fadehue(leds,15,160,255,dim8_video(200),10,NUM_LEDS);
  // rainbowfade(leds, saturation, brightness, 15, NUM_LEDS);
  // rainbowbreathe(leds, 255, brightness, 10, NUM_LEDS);
  vTaskDelay(1000);
}
