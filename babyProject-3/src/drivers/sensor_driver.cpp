#include <Arduino.h>
#include "drivers/sensor_driver.h"

SensorDriver::SensorDriver(uint8_t pinSensor, uint8_t DHTtype) : _dht(pinSensor, DHTtype) {};

void SensorDriver::sensor_init() {
    _dht.begin();
};

float SensorDriver::read_sensor() {
    float t = _dht.readTemperature();

    if (isnan(t)){
        Serial.println("Failed to read from DHT sensor!");
        return 0.0;
    };
    
    return t;
};

