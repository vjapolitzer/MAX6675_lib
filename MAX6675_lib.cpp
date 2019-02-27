#include "Arduino.h"
#include "MAX6675_lib.h"
#include "SPI.h"

MAX6675::MAX6675(int8_t CS)
{
    this->cs = CS;
    pinMode(this->cs, OUTPUT);
    digitalWrite(this->cs, HIGH);
}

double MAX6675::readCelsius()
{
    uint16_t data;
    // SPI clock speed:4.3MHz, Data Shift:MSB First, Data Clock Idle: SPI_MODE0
    SPI.beginTransaction(SPISettings(4300000, MSBFIRST, SPI_MODE0));
    // Select the chip, stopping the conversion process
    digitalWrite(this->cs, LOW);
    // Read in bits 15-8
    data = SPI.transfer(0x00);
    data <<= 8;
    // Read in bits 7-0
    data |= SPI.transfer(0x00);
    // Deselect the chip, intiating a new conversion process
    digitalWrite(this->cs, HIGH);
    SPI.endTransaction();

    // Check bit 2, which indicates whether the thermocouple is disconnected
    if (data & 0x4) return NAN;
    // Get rid of bits 2-0 (State, Device ID, Thermocouple Input)
    data >>= 3;
    // Scale the data, which is ~4x the actual value (4096 -> 1023.75C)
    return data * 0.25;
}

double MAX6675::readFahrenheit()
{
    return (readCelsius() * 1.8) + 32.0;
}