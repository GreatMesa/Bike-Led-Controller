#pragma once

#include <Wire.h>
#include <string>
#include "Arduino.h"
/*
    INA236 Register Map
    - Register 0x00 -> (Configuration Register) Register used to configure the INA236. (Read / Write)
    - Register 0x01 -> (Shunt Voltage Register) 16-bit 2's complement value for the shunt resistor voltage (Volts). (Read only)
    - Register 0x02 -> (Bus Voltage Register) 16-bit 2's complement value for the bus voltage (Volts). (Read only)
    - Register 0x03 -> (Power Register) 16-bit 2's complement value for the power of the system (Watts). (Read only)
    - Register 0x04 -> (Current Register) 16-bit 2's complement value for the current of the system (Amperes). (Read only)
    - Register 0x05 -> (Callibration Register) Register that stores the shunt resistor value connected to the INA236 (Ohms). (Read / Write)
    - Register 0x06 -> (Mask-Enable Register) Register that configures the alert pin of the INA236. (Read / Write)
    - Register 0x07 -> (Alert-Limit Register) Register used to configure a value for alert pinging. (Read / Write)
    - Register 0x3E -> (Manufacturer ID) Reads back TI in ASCII (8473). (Read only)
    - Register 0x3E -> (Device ID) Stores back the device identification bits for device communication verification. (Read only)
*/
#define INA_CONFIG_REGISTER 0x00
#define SHUNT_VOLTAGE_REGISTER 0x01
#define VOLTAGE_REGISTER 0x02
#define POWER_REGISTER 0x03
#define CURRENT_REGISTER 0x04
#define CALLIBRATION_REGISTER 0x05
#define MASK_ENABLE_REGISTER 0x06
#define ALERT_REGISTER 0x07
#define DEVICE_ID 0x3F

// Configuration Bit Map
#define INA236_CONFIG_RST 0b0
#define INA236_CONFIG_ADC_RANGE 0b1
#define INA236_CONFIG_AVG 0b001
#define INA236_CONFIG_VBUSCT 0b100
#define INA236_CONFIG_VSHCT 0b100
#define INA236_CONFIG_MODE 0b111

// Mask-Enable Bit Map
#define SOL 0b0
#define SOH 0b0
#define BOL 0b0
#define BUL 0b0
#define POL 0b0
#define CNVR 0b1
#define APOL 0b0
#define LEN 0b0

// Callibration Register Map
#define INA236_MAX_CURRENT 5
#define INA236_SHUNT_RESISTANCE 0.01

class ina236
{
private:
    uint16_t config;
    uint16_t callibration;
    uint16_t raw_current;
    uint16_t raw_voltage;
    uint16_t raw_power;
    uint16_t shunt_cal;

    float current;
    float voltage;
    float power;
    float current_lsb;

public:
    /*
    @brief
    Sets the configuration value used in the INA236.
    */
    uint16_t configurate();
    /*
        @brief
        Callibrates the INA236
        @param maxCurrent Maximum expected current draw.
        @param shuntResistance Shunt resistor resistance.

    */
    uint16_t callibrate(float maxCurrent, float shuntResistance);

    /*
        @brief
        Initializes the INA236 Class and returns a message.
    */
    std::string initialize();
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
    @brief Obtains the current draw through the INA236.
    */
    float getCurrent();
    /*
    @brief Obtains the bus votlage through the INA236.
    */
    float getVoltage();
    /*
    @brief Obtains the power draw through the INA236.
    */
    float getPower();
    /*
        @brief Updates the current, voltage, and power values from the INA236.
    */
    void updateINA236();
    /*
    @brief Prints the current, voltage, and power values from the INA236.
    */
    void printINA236();
};