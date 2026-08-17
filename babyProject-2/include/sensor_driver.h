#pragma once
#include "DHT.h"

#define DHTTYPE DHT11

class SensorDriver {
    private:
        DHT _dht;
    public:
        SensorDriver();
        
        void sensor_init();
        float tempt_read();
};