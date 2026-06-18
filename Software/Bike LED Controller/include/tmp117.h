#pragma once

#include "Wire.h"
#include <string>
#include "Arduino.h"

#define TMP117_MODE 0b00
#define TMP117_CONVERSION_CYCLE 0b000
#define TMP117_AVERAGE 0b00
#define TMP117_TNA 0b0
#define TMP117_POLARITY 0b0
#define TMP117_DRALERT 0b0
#define TMP117_SRST 0b0
class tmp117
{
private:
    uint16_t raw_temp;
    uint16_t config;

    float temp;

public:
    /*
    @brief
    Sets the configuration value used in the TMP117.
    */
    uint16_t configurate();

    /*
        @brief
        Initializes the INA236 Class and returns a message.
    */
    bool initialize();
    /*
            @brief Writes a 16-Bit value to a specified register.
            @param reg The wanted register to be written to.
            @param value The value to be written to the register.
        */
    bool writeRegister(uint8_t reg, uint16_t value);
    /*
        @brief Reads a spesific 16-Bit Register
        @param reg The wanted register to be read from.
    */
    uint16_t readRegister(uint8_t reg);
    /*
        @brief Obtains the temperature value from the TMP117.
    */
   float getTemperature();
   /*
    @brief Print out the temperature value from the TMP117
   */
    void printTemperature();
};