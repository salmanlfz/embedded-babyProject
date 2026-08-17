#include "sensor_driver.h"
#include "config.h"

SensorDriver::SensorDriver() : _dht(PIN_TEMPT_SENSOR, DHTTYPE) {

}

void SensorDriver::sensor_init(){
    _dht.begin();
}

float SensorDriver::tempt_read(){
    float t = _dht.readTemperature();

    if (isnan(t)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return 0;
    }

    return t; 
}