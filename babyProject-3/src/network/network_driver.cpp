#include "network/network_driver.h"
#include "config.h"
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

QueueHandle_t NetworkDriver::tempt_threshold = nullptr;

NetworkDriver::NetworkDriver() : client(espClient) {};

void NetworkDriver::network_init() {
    if (tempt_threshold == nullptr){
        tempt_threshold = xQueueCreate(1, sizeof(float));
    }
    
    WiFi.begin(ssid, password);

    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(mqtt_callback);
};

void NetworkDriver::mqtt_callback(char *topic, byte *payload, unsigned int length) {
    char buff[length + 1];
    memcpy(buff, payload, length);
    buff[length] = '\0';

    float threshold = atof(buff);

    if (tempt_threshold != nullptr){
        xQueueOverwrite(tempt_threshold, &threshold);
    }

    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message: ");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
        // message += (char)payload[i];
    }
    // Serial.println(message);
    Serial.println();
    Serial.println("------------");
};

void NetworkDriver::mqtt_publish(char *message) {
    if (client.connected()) {
        client.publish(topic_pub, message);
    }
};

void NetworkDriver::mqtt_loop(){
    if (WiFi.status() != WL_CONNECTED){
        return;
    }
    Serial.println("WiFi Connected");
    
    if (!client.connected()) {
        if (client.connect("ESP32Client")) {
            Serial.println("MQTT Broker Connected!");
            client.subscribe(topic_sub);
        } else {
            Serial.println("MQTT Failed to Connect");
            return;
        }
    }

    client.loop();
};


