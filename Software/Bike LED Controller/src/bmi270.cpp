#include "bmi270.h"
#include "Arduino.h"

SPISettings settings(1000000, MSBFIRST, SPI_MODE0);

void bmi270::writeRegister(uint8_t reg, uint8_t val)
{
    spi->beginTransaction(settings);
    digitalWrite(5, LOW);
    delayMicroseconds(1);
    spi->transfer(reg & 0x7F);
    spi->transfer(val);
    digitalWrite(5, HIGH);
    spi->endTransaction();
    delayMicroseconds(450); // required idle after write in suspend/low-power mode
}

uint8_t bmi270::readRegister(uint8_t reg)
{
    spi->beginTransaction(settings);
    digitalWrite(5, LOW);
    delayMicroseconds(1);
    spi->transfer(reg | 0x80);
    spi->transfer(0x00); // dummy byte
    uint8_t val = spi->transfer(0x00);
    digitalWrite(5, HIGH);
    spi->endTransaction();
    delayMicroseconds(2); // required 2us idle after read
    return val;
}

bool bmi270::initialize()
{
    spi = &SPI;
    pinMode(5, OUTPUT);
    digitalWrite(5, HIGH);
    pinMode(19, INPUT_PULLDOWN);
    delay(10);

    spi->begin(18, 19, 23, -1);
    delay(10);

    // Dummy read to switch device from I2C mode to SPI mode
    // Result is invalid by design per datasheet section 6.3
    readRegister(0x00);
    delayMicroseconds(200);
    int pass = 0, fail = 0;
    for (int i = 0; i < 100; i++)
    {
        uint8_t id = readRegister(0x00);
        if (id == 0x24)
            pass++;
        else
            fail++;
        delay(10);
    }

    Serial.println(pass);
    Serial.println(fail);

    uint8_t id = readRegister(0x00);
    if (id != 0x24)
        return false;

    return true;
}