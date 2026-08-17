#pragma once

class AlarmDriver {
    public:
        void led_init();
        void buzzer_init();

        void led_toggle();
        void buzzer_control(bool state);
};