#pragma once
#include <stdint.h>

class AlarmDriver {
    private:
        uint8_t _pin_led;
        uint8_t _pin_buzzer;
    public:
        AlarmDriver(uint8_t pinLED, uint8_t pinBuzzer);

        void led_init();
        void buzzer_init();

        void led_toggle();
        void buzzer_controller(bool state);
};