#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

class NetworkDriver {
    private: 
        WiFiClient espClient;
        PubSubClient client;

        static void mqtt_callback(char *topic, byte *payload, unsigned int length);
    public:
        static QueueHandle_t tempt_threshold;
        
        NetworkDriver();

        void network_init();

        void mqtt_publish(char *message);
        void mqtt_subscribe();
        void mqtt_loop();
};