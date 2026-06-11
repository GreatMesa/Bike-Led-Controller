#include "tmp117.h"

uint16_t tmp117::configurate()
{
    config = ((TMP117_MODE << 10)
            + (TMP117_CONVERSION_CYCLE << 7)
            + (TMP117_AVERAGE << 5)
            + (TMP117_TNA << 4)
            + (TMP117_POLARITY << 3)
            + (TMP117_DRALERT << 2)
            + (TMP117_SRST << 1) );
    return config;
}

bool tmp117::writeRegister(uint8_t reg, uint16_t value)
{
    Wire.beginTransmission(0x48);

    Wire.write(reg);
    Wire.write((value << 8) & 0xFF);
    Wire.write(value & 0xFF);
    Wire.endTransmission();
    return 1;
}

uint16_t tmp117::readRegister(uint8_t reg)
{
    Wire.beginTransmission(0x48);
    Wire.write(reg);
    Wire.endTransmission(false);

    Wire.requestFrom(0x48, 2);
    if (Wire.available() >= 2)
    {
        uint8_t high = Wire.read();
        uint8_t low = Wire.read();
        uint16_t value = (high << 8) | (low);
        return value;
    }
    return 0;
}

std::string tmp117::initialize()
{
    uint16_t id = readRegister(0x0F);
    if (id != 0x117)
    {
        Serial.println(id);
        return "TMP117 ID Incorrect. TMP117 Not Initialized.";
    }

    configurate();
    writeRegister(0x01, config);

    return "TMP117 Initialized.";
}

float tmp117::getTemperature()
{
    int16_t raw_temp = readRegister(0x00);
    temp = raw_temp * (7.8125 / 1000);
    return temp;
}

void tmp117::printTemperature()
{
    getTemperature();
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" C.");
}