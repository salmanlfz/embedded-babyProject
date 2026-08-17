#include <Arduino.h>
#include "drivers/alarm_driver.h"

AlarmDriver::AlarmDriver(uint8_t pinLED, uint8_t pinBuzzer) : _pin_led(pinLED), _pin_buzzer(pinBuzzer) {};

void AlarmDriver::led_init() {
    pinMode(_pin_led, OUTPUT);
};

void AlarmDriver::buzzer_init() {
    pinMode(_pin_buzzer, OUTPUT);
};

void AlarmDriver::led_toggle() {
    digitalWrite(_pin_led, !digitalRead(_pin_led));
};

void AlarmDriver::buzzer_controller(bool state) {
    digitalWrite(_pin_buzzer, state);
}


