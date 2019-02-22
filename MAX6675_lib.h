/**********************************************************************************************
 * Arduino MAX6675 Library - Version 1.0
 * by Vincent Politzer
 * 
 * inspired by Limor Fried's MAX6675 library
 * 
 * This Library is licensed under the MIT License
 **********************************************************************************************/

#ifndef MAX6675_LIB_H
#define MAX6675_LIB_H
#include "Arduino.h"

class MAX6675 {
    public:
        /* Constructor
        * ...Parameters:
        * ......int8_t CS -- Pin used for MAX6675's CS
        * ...Returns:
        * ......Nothing
        */
        MAX6675(int8_t CS);

        /* readCelsius()
        * ...Reads temperature from the MAX6675 over HW SPI
        * ...Returns:
        * ......Temperature in Celsius, or NaN if TC disconnected
        */
        double readCelsius(void);

        /* readFahrenheit()
        * ...Reads temperature from the MAX6675 over HW SPI
        * ...Returns:
        * ......Temperature in Fahrenheit, or NaN if TC disconnected
        */
        double readFahrenheit(void);

    private:
        int8_t cs;
};
#endif