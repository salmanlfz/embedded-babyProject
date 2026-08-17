#pragma once 
#include <Arduino.h>
#include <stdint.h>
#include "DHT.h"

class SensorDriver {
    private:
        DHT _dht;
    public:
        SensorDriver(uint8_t pinSensor, uint8_t dhTtype);

        void sensor_init();
        float read_sensor();
};