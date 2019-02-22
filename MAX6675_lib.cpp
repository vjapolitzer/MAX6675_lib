#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdlib.h>
#include "MAX6675_lib.h"
#include "SPI.h"

MAX6675::MAX6675(int8_t CS ) {
    this->cs = CS;
    pinMode(cs, OUTPUT);
    digitalWrite(cs, HIGH);
}

double MAX6675::readCelsius(void) {
  uint16_t v;
  //SPI clock speed:4.3MHz, Data Shift:MSB First, Data Clock Idle: SPI_MODE0
  SPI.beginTransaction(SPISettings(4300000, MSBFIRST, SPI_MODE0));
  digitalWrite(cs, LOW);
  _delay_ms(1);

  v = SPI.transfer(0x00);
  v <<= 8;
  v |= SPI.transfer(0x00);

  digitalWrite(cs, HIGH);
  SPI.endTransaction();

  if (v & 0x4) return NAN; // Thermocouple disconnected!

  v >>= 3;

  return v*0.25;
}

double MAX6675::readFahrenheit(void) {
  return readCelsius() * (9.0 / 5.0) + 32;
}