#include "storage/storage_driver.h"
#include "config.h"
#include <Arduino.h>
#include <Preferences.h>

void StorageDriver::storage_init() {
    _prefs.begin("temp-sensor", false);
    _prefs.end();
}

float StorageDriver::get_threshold() {
    _prefs.begin("temp-sensor", true);

    float threshold = _prefs.getFloat("max-temp", DEFAULT_MAX_TEMPT);

    _prefs.end();

    return threshold;
}

void StorageDriver::save_threshold(float threshold){
    _prefs.begin("temp-sensor", false);
    _prefs.putFloat("max-temp", threshold);
    _prefs.end();
}