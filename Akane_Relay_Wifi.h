#ifndef _AKANE_RELAY_WIFIH_
#define _AKANE_RELAY_WIFIH_

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "Akane_Settings.h"
#include "Akane_Sensor_Wifi.h"
#include "Akane_Logger.h"
#include "Observer.h"

class Akane_Relay_Wifi : public Akane_Relay {
  private:
    char* ssid;
    char* ssid_pwd;
    uint8_t status;
    uint8_t prev_status;
    bool should_be_connected;
    
  public:
    Akane_Relay_Wifi(const char* ssid, const char* ssid_pwd, bool is_connected): Akane_Relay(-1) { 
      should_be_connected = is_connected; 

      prev_status = WL_IDLE_STATUS;
      ESP8266WebServer server(ESP8266_PORT);
    };
    inline void setActive(bool pActive) {
      should_be_connected = pActive;
      
      if(pActive && !isActive()) {
        Akane_Logger::log("[Akane_Relay_Wifi][setActive] Wifi is not active. Tring to connect...");
        WiFi.begin(ssid, ssid_pwd);

        // Wait for connection
        unsigned int nb_check = 0;
        while (WiFi.status() != WL_CONNECTED && nb_check < 3) {
          Akane_Logger::log("[Akane_Relay_Wifi][setActive] Trying to connect #" + String(nb_check + 1));
          delay(500);
          nb_check++;
        }
      }
      else if(pActive && isActive()) {
        Akane_Logger::log("[Akane_Relay_Wifi][setActive] Wifi is active. Tring to disconnect...");
        WiFi.disconnect(); 
      }

      status = WiFi.status();
    };
    inline bool isActive() {
      status = WiFi.status();
      Akane_Logger::log("[Akane_Relay_Wifi][isActive] Getting Wifi status..." + String(status));
      return status == WL_CONNECTED;
    };
    inline String getLocalIP() {
      if(isActive()) {
        return WiFi.localIP().toString();
      }
      return "0.0.0.0";
    };
    inline virtual void update(Akane_Sensor *observable) {
      uint8_t res = (uint8_t) observable->get_value();
      Akane_Logger::log("[Akane_Relay_Wifi][update] Receive value is: " + String(res));

      /*
       * WL_IDLE_STATUS = 0,
       * WL_NO_SSID_AVAIL = 1,
       * WL_SCAN_COMPLETED = 2,
       * WL_CONNECTED = 3,
       * WL_CONNECT_FAILED = 4,
       * WL_CONNECTION_LOST = 5,
       * WL_DISCONNECTED = 6
       */

      if((res != WL_CONNECTED && should_be_connected) || (res != WL_DISCONNECTED && !should_be_connected)) {
        setActive(should_be_connected);
      }
        
      if(prev_status != res) {
        Akane_Logger::log("[Akane_Relay_Wifi][update] Status has changed (" + String(prev_status) + " to " + String(res) + ")");
        Akane_Screen::getInstance().display_wifi_status(res == WL_CONNECTED);
      }
      prev_status = res;
      status = res;
    };
};

#endif
