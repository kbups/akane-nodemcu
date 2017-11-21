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
      Akane_Logger::log("[Akane_Observer_MQTT][mqtt_callback] Message arrived / Topic: " + String(topic));

      String str_payload = "";
      for (int i = 0; i < length; i++) {
        str_payload = str_payload + (char)payload[i];
      }
      
      Akane_Logger::log("[Akane_Observer_MQTT][mqtt_callback] Payload: " + str_payload);

      // SENSORS
      // /home/akane/humidity
      // /home/akane/temperature
      // /home/akane/waterlevel
      // /home/akane/light

      // RELAYS
      // /home/akane/heater
      // /home/akane/fan
      // /home/akane/misting
      // /home/akane/fogger

      String str_topic = String(topic);

      if(str_topic.equals("/home/akane/temperature")) {
        float res_t = str_payload.toFloat();
        Akane_Screen::getInstance().display_temperature(res_t);
      }
      else if(str_topic.equals("/home/akane/humidity")) {
        float res_h = str_payload.toFloat();
        Akane_Screen::getInstance().display_humidity(res_h);
      }
      else if(str_topic.equals("/home/akane/waterlevel")) {
        float res_w = str_payload.toFloat();
        Akane_Screen::getInstance().display_waterlevel(res_w);
      }
      else if(str_topic.equals("/home/akane/light")) {
        float res_l = str_payload.toFloat();
        Akane_Screen::getInstance().display_light(res_l);
      }
      else if(str_topic.equals("/home/akane/relays")) {
        // Payload: {"distance":5.1000000000000005,"relay":"3:ON","MCP23017":12,"relays":{"2":"ON","3":"ON"}}
        int idx1 = str_payload.indexOf("relays");
        if(idx1 > -1) {
          int idx2 = str_payload.indexOf("}", idx1);
          if(idx2 > -1) {
            String relays_str = str_payload.substring(idx1 + 9, idx2);
            Akane_Logger::log("[Akane_Observer_MQTT][mqtt_callback] Relays: " + relays_str);
            
            int idxr1;
            int idxr2;
            String status;
            if(relays_str.indexOf("0") > -1) {
              idxr1 = relays_str.indexOf("0") + 4;
              idxr2 = relays_str.indexOf("\"", idxr1);
              status = relays_str.substring(idxr1, idxr2);

              Akane_Logger::log("[Akane_Observer_MQTT][mqtt_callback] Relay HEATER: " + status);
              Akane_Screen::getInstance().update_heater_status(status == "ON");
            }
            if(relays_str.indexOf("1") > -1) {
              idxr1 = relays_str.indexOf("1") + 4;
              idxr2 = relays_str.indexOf("\"", idxr1);
              status = relays_str.substring(idxr1, idxr2);

              Akane_Logger::log("[Akane_Observer_MQTT][mqtt_callback] Relay FAN: " + status);
              Akane_Screen::getInstance().update_fan_status(status == "ON");
            }
            if(relays_str.indexOf("2") > -1) {
              idxr1 = relays_str.indexOf("2") + 4;
              idxr2 = relays_str.indexOf("\"", idxr1);
              status = relays_str.substring(idxr1, idxr2);
              
              Akane_Logger::log("[Akane_Observer_MQTT][mqtt_callback] Relay FOGGER: " + status);
              Akane_Screen::getInstance().update_fogger_status(status == "ON");
            }
            if(relays_str.indexOf("3") > -1) {
              idxr1 = relays_str.indexOf("3") + 4;
              idxr2 = relays_str.indexOf("\"", idxr1);
              status = relays_str.substring(idxr1, idxr2);

              Akane_Logger::log("[Akane_Observer_MQTT][mqtt_callback] Relay MISTING: " + status);
              Akane_Screen::getInstance().update_misting_status(status == "ON");
            }
            if(relays_str.indexOf("4") > -1) {
              idxr1 = relays_str.indexOf("4") + 4;
              idxr2 = relays_str.indexOf("\"", idxr1);
              status = relays_str.substring(idxr1, idxr2);

              Akane_Logger::log("[Akane_Observer_MQTT][mqtt_callback] Relay LIGHT: " + status);
              Akane_Screen::getInstance().update_light_status(status == "ON");
            }
          }
        }
        
        /*bool res_ht = str_payload == "1" || str_payload == "ON";
        Akane_Screen::getInstance().update_heater_status(res_ht);
        Akane_Screen::getInstance().update_fan_status(res_ht);
        Akane_Screen::getInstance().update_misting_status(res_ht);
        Akane_Screen::getInstance().update_fogger_status(res_ht);*/
      }
    };

    inline void reconnect() {
      // Loop until we're reconnected
      while (!client->connected()) {
        Akane_Logger::log("[Akane_Observer_MQTT][mqtt_callback] Attempting MQTT connection...");
        // Attempt to connect
        if (client->connect("ESP8266Client")) {
          Akane_Logger::log("[Akane_Observer_MQTT][mqtt_callback] Connected!");

          Akane_Logger::log("[Akane_Observer_MQTT][mqtt_callback] Subscribe to /home/# subjects");
          client->subscribe("/home/#");

          Akane_Logger::log("[Akane_Observer_MQTT][mqtt_callback] Telling the server everything is ok...");
          client->publish("/home/akane/initialize", "HELO");
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

