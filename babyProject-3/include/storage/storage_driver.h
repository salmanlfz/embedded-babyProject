#pragma once 
#include "Preferences.h"

class StorageDriver {
    private:
        Preferences _prefs;
    public:
        void storage_init();
        float get_threshold();
        void save_threshold(float threshold);
};