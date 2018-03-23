#ifndef _AKANE_RELAY_WIFIH_
#define _AKANE_RELAY_WIFIH_

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "Akane_Settings.h"
#include "Akane_Sensor_Wifi.h"
#include "Akane_Logger.h"
#include "Observer.h"

#define WIFI_AP_SSID "Akane"
#define WIFI_AP_PWD "Akane"

class Akane_Observer_Wifi : public Observer<Akane_Sensor> {
  private:
    uint8_t status;
    uint8_t prev_status;
    String prev_ip_address;
    bool should_be_connected;
    
  public:
    Akane_Observer_Wifi(bool is_connected) {
      should_be_connected = is_connected; 

      prev_status = WL_IDLE_STATUS;
      prev_ip_address = "0.0.0.0";

      WiFi.hostname("Akane");
      ESP8266WebServer server(ESP8266_PORT);

      WiFi.softAP(WIFI_AP_SSID, WIFI_AP_PWD);
    };
    inline void setActive(bool pActive) {
      should_be_connected = pActive;
      
      if(pActive && !isActive()) {
        Akane_Logger::log("[Akane_Relay_Wifi][setActive] Wifi is not active. Tring to connect...");
        
        WiFi.begin(Akane_Settings::getInstance().get_ssid(), Akane_Settings::getInstance().get_ssid_pwd());
        
        // Wait for connection
        unsigned int nb_check = 0;
        while (WiFi.status() != WL_CONNECTED && nb_check < 3) {
          Akane_Logger::log("[Akane_Relay_Wifi][setActive] Trying to connect #" + String(nb_check + 1));
          delay(500);
          nb_check++;
        }
      }
      else if(pActive && isActive()) {
        Akane_Logger::log("[Akane_Relay_Wifi][setActive] Wifi is active. Trying to disconnect...");
        WiFi.disconnect(); 
      }

      status = WiFi.status();

      Akane_Screen::getInstance().display_wifi_ap_status(getLocalIP_AP());
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
    
    inline String getLocalIP_AP() { 
      return WiFi.softAPIP().toString();
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

      String ip_address = getLocalIP();
        
      if(prev_status != res || prev_ip_address != ip_address) {
        Akane_Logger::log("[Akane_Relay_Wifi][update] Status has changed: " + String(prev_status) + " to " + String(res) + " AND " + prev_ip_address + " to " + ip_address);
        Akane_Screen::getInstance().display_wifi_status(res == WL_CONNECTED, ip_address, prev_ip_address);
      }
      prev_status = res;
      prev_ip_address = ip_address;
      status = res;
    };
};

#endif
