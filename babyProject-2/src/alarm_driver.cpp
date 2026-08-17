#include "config.h"
#include "alarm_driver.h"

void AlarmDriver::led_init(){
    pinMode(PIN_LED, OUTPUT);
}

void AlarmDriver::buzzer_init(){
    pinMode(PIN_BUZZER, OUTPUT);
}

void AlarmDriver::led_toggle(){
    digitalWrite(PIN_LED, !digitalRead(PIN_LED));
}

void AlarmDriver::buzzer_control(bool state){
    digitalWrite(PIN_BUZZER, state);
}
