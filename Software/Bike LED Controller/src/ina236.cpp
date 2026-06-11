#include "ina236.h"

uint16_t ina236::configurate()
{
    config = ((INA236_CONFIG_RST << 15) |
              (INA236_CONFIG_ADC_RANGE << 12) |
              (INA236_CONFIG_AVG << 9) |
              (INA236_CONFIG_VBUSCT << 6) |
              (INA236_CONFIG_VSHCT << 3) |
              INA236_CONFIG_MODE);
    return config;
}

uint16_t ina236::callibrate(float maxCurrent, float shuntResistance)
{
    // Converts shunt resistor value into needed shunt constant.
    current_lsb = (INA236_MAX_CURRENT / 32768.0f);
    shunt_cal = ((0.00512f) / ((INA236_SHUNT_RESISTANCE) * (current_lsb))) / 4;
    return shunt_cal;
}
bool ina236::writeRegister(uint8_t reg, uint16_t value)
{
    Wire.beginTransmission(0x40);

    Wire.write(reg);
    Wire.write((value << 8) & 0xFF);
    Wire.write(value & 0xFF);
    Wire.endTransmission();
    return 1;
}

uint16_t ina236::readRegister(uint8_t reg)
{
    Wire.beginTransmission(0x40);
    Wire.write(reg);
    Wire.endTransmission(false);

    Wire.requestFrom(0x40, 2);
    if (Wire.available() >= 2)
    {
        uint8_t high = Wire.read();
        uint8_t low = Wire.read();
        uint16_t value = (high << 8) | (low);
        return value;
    }
    return 0;
}

std::string ina236::initialize()
{
    uint16_t id = readRegister(0x3E);
    if (id != 0x5449)
    {
        Serial.println(id);
        return "INA236 ID Incorrect. INA236 Not Initialized.";
    }

    configurate();
    writeRegister(0x00, config);

    callibrate(INA236_MAX_CURRENT, INA236_SHUNT_RESISTANCE);
    writeRegister(0x05, callibration);

    writeRegister(0x06, 0b0000010000000000);

    return "INA236 Initialized.";
}

float ina236::getCurrent()
{
    raw_current = readRegister(0x04);
    current = raw_current * current_lsb;
    return current;
}

float ina236::getVoltage()
{
    raw_voltage = readRegister(0x02);
    voltage = raw_voltage * 0.0016f;
    return voltage;
}

float ina236::getPower()
{
    raw_power = readRegister(0x03);
    power = raw_power * current_lsb * 32;
    return power;
}

void ina236::updateINA236()
{
    getCurrent();
    getVoltage();
    getPower();
}

void ina236::printINA236()
{
    updateINA236();
    Serial.print("Current: ");
    Serial.print(current);
    Serial.println(" Amps");

    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.println(" Volts");

    Serial.print("Power: ");
    Serial.print(power);
    Serial.println(" Watts");
}