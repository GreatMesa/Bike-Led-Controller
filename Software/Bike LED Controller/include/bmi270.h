#include "SPI.h"
#include <string>

class bmi270
{
    private:
    // Raw Acceleration / Gyroscope Values
    uint16_t raw_accel[3];
    uint16_t raw_gyro[3];

    // Actual Accelerometer / Gyroscope Values
    float accel[3];
    float gyro[3];
    // Other Variables
    SPIClass * spi;
    public:
    bool initialize();

    void writeRegister(uint8_t reg, uint8_t val);
    uint8_t readRegister(uint8_t reg);
    void readAccel();
    void readGyr();
};