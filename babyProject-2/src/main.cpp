#include <Arduino.h>
#include "config.h"
#include "alarm_driver.h"
#include "sensor_driver.h"

AlarmDriver myAlarm;
SensorDriver sensor;

volatile float current_temp = 0.0;
volatile bool warning_state = false;

void check_temperature(void *pvParameter){
  for(;;){
    current_temp = sensor.tempt_read();
    
    Serial.print("current temp: ");
    Serial.println(current_temp);
    
    if (current_temp > MAX_TEMPT) {
      warning_state = true;
    } else {
      warning_state = false;
    }

    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void LED_indicator(void *pvParameter){
  for(;;){
    myAlarm.led_toggle();

    if (warning_state){
      vTaskDelay(100/portTICK_PERIOD_MS);
    } else {
      vTaskDelay(1000/portTICK_PERIOD_MS);
    }
  }
}

void buzzer_indicator(void *pvParameter){
  for(;;){
    myAlarm.buzzer_control(warning_state);
    vTaskDelay(200/portTICK_PERIOD_MS);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  sensor.sensor_init();

  myAlarm.led_init();
  myAlarm.buzzer_init();

  xTaskCreate(
    check_temperature,
    "check temperature",
    2048,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    LED_indicator,
    "LED Indicator", 
    1024,
    NULL,
    1,
    NULL
  );

  xTaskCreate(
    buzzer_indicator,
    "Buzzer Indicator",
    1024,
    NULL,
    2,
    NULL
  );
}

void loop() {
  // put your main code here, to run repeatedly:
}
