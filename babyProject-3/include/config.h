#pragma once
#include <Arduino.h>
#include <stdint.h>

// HARDWARE PIN
const uint8_t PIN_LED = 2;
const uint8_t PIN_BUZZER = 5; 
const uint8_t PIN_TEMP_SENSOR = 18;

// WiFi CONFIGURATION
inline const char *ssid = "mr.dee";
inline const char *password = "TanyaUmie";

// MQTT CONFIGURATION
inline const char *mqtt_broker = "broker.emqx.io";
inline const char *topic_pub = "babyProject/current_temp";
inline const char *topic_sub = "babyProject/threshold";
inline const int mqtt_port = 1883;

// DEFAULT VALUE
const float DEFAULT_MAX_TEMPT = 32.0;
const int baud_rate = 9600;
