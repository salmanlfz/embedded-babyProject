#include <Arduino.h>
#include "config.h"
#include "drivers/alarm_driver.h"
#include "drivers/sensor_driver.h"
#include "freertos/portmacro.h"
#include "freertos/projdefs.h"
#include "network/network_driver.h"
#include "storage/storage_driver.h"

AlarmDriver myAlarm(PIN_LED, PIN_BUZZER);
SensorDriver mySensor(PIN_TEMP_SENSOR, DHT11);
NetworkDriver network;
StorageDriver storage;

QueueHandle_t warning_state;
QueueHandle_t tempt_data;


void TaskAlarm(void *pvParameter){
  bool warning = false;
  int led_delay = 1000;

  for(;;){
    // sensor get the data every 1000ms thats why if u put the led and buzzer in this "if" will keep run every 1000ms eventhough the delay is changed to 200ms
    if (xQueueReceive(warning_state, &warning, 0) == pdTRUE) {
      if (warning){
        led_delay = 200;
      } else {
        led_delay = 1000;
      }

    }
    myAlarm.buzzer_controller(warning);
    myAlarm.led_toggle();

    vTaskDelay(led_delay / portTICK_PERIOD_MS);
  }
}

void TaskReadSensor(void *pvParameter){
  bool warning = false;
  char buff[16];

  for(;;){
    float tempt = mySensor.read_sensor();
    
    if (tempt > storage.get_threshold()) {
      warning = true;
    } else {
      warning = false;
    }
    
    xQueueOverwrite(tempt_data, &tempt);
    xQueueOverwrite(warning_state, &warning);

    // Format float ke String dengan snprintf
    snprintf(buff, sizeof(buff), "%.2f", tempt);
    network.mqtt_publish(buff);

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void TaskNetwork(void *pvParameter){
  for(;;) {
    network.mqtt_loop();

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void TaskMemory(void *pvParameter){
  float threshold;

  for(;;){
    if (xQueueReceive(network.tempt_threshold, &threshold, 0) == pdTRUE){
      if (threshold != storage.get_threshold()){
        storage.save_threshold(threshold);
      }
    }

    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(baud_rate);

  tempt_data = xQueueCreate(1, sizeof(float));
  warning_state = xQueueCreate(1, sizeof(bool));

  myAlarm.led_init();
  myAlarm.buzzer_init();
  mySensor.sensor_init();

  network.network_init();
  storage.storage_init();

  xTaskCreate(TaskAlarm, "Alarm Task", 2048, NULL, 2, NULL);
  xTaskCreate(TaskReadSensor, "Read Sensor", 4096, NULL, 1, NULL);
  xTaskCreate(TaskNetwork, "WiFi and MQTT Connection", 4096, NULL, 1, NULL);
  xTaskCreate(TaskMemory, "Get threshold", 2048, NULL, 1, NULL);
}

void loop() {
  // put your main code here, to run repeatedly:
}