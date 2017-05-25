#ifndef _AKANE_OBSERVER_MQTTH_
#define _AKANE_OBSERVER_MQTTH_

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

#include "Akane_Settings.h"
#include "Akane_Logger.h"
#include "Observer.h"

class Akane_Observer_MQTT : public Akane_Sensor {
  private:
    WiFiClient espClient;
    PubSubClient* client;
    
  public:
    Akane_Observer_MQTT() : Akane_Sensor("MQTT", 0) {
      client = new PubSubClient(espClient);

      client->setServer("192.168.1.50", 1883);
      client->setCallback(&Akane_Observer_MQTT::mqtt_callback);
    };
    /*
    inline virtual void update(Akane_Sensor *observable) {
      uint8_t res = (uint8_t) observable->get_value();
      Akane_Logger::log("[Akane_Observer_MQTT][update] Receive value is: " + String(res));
*/
      /*
       * WL_IDLE_STATUS = 0,
       * WL_NO_SSID_AVAIL = 1,
       * WL_SCAN_COMPLETED = 2,
       * WL_CONNECTED = 3,
       * WL_CONNECT_FAILED = 4,
       * WL_CONNECTION_LOST = 5,
       * WL_DISCONNECTED = 6
       */
/*
      if(res == WL_CONNECTED && !client->connected()) {
        // TODO
      }
    };*/

    inline static void mqtt_callback(char* topic, byte* payload, unsigned int length) {
      Akane_Logger::log("[Akane_Observer_Wifi][mqtt_callback] Message arrived / Topic: " + String(topic));

      String str_payload = "";
      for (int i = 0; i < length; i++) {
        str_payload = str_payload + (char)payload[i];
      }
      
      Akane_Logger::log("[Akane_Observer_MQTT][mqtt_callback] Payload: " + str_payload);
    
      // /home/akane/humidity
      // /home/akane/temperature

      String str_topic = String(topic);

      if(str_topic.equals("/home/akane/temperature")) {
        float res_t = str_payload.toFloat();
        Akane_Screen::getInstance().display_temperature(res_t);
      }
      else if(str_topic.equals("/home/akane/humidity")) {
        float res_h = str_payload.toFloat();
        Akane_Screen::getInstance().display_humidity(res_h);
      }
    };

    inline void reconnect() {
      // Loop until we're reconnected
      while (!client->connected()) {
        Akane_Logger::log("[Akane_Observer_MQTT][mqtt_callback] Attempting MQTT connection...");
        // Attempt to connect
        if (client->connect("ESP8266Client")) {
          Akane_Logger::log("[Akane_Observer_MQTT][mqtt_callback] Connected!");
          client->subscribe("/home/#");
        } else {
          Akane_Logger::log("[Akane_Observer_MQTT][mqtt_callback] Failed, rc=" + String(client->state()) + ". Try again in 5 seconds");
          // Wait 5 seconds before retrying
          delay(5000);
        }
      }
    };

    virtual void read_value() {
      Akane_Logger::log("[Akane_Observer_MQTT] Reading sensor value...");
      if (!client->connected()) {
        reconnect();
      }
      client->loop();
    }
};

#endif

