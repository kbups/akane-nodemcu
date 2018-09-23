#ifndef _AKANE_RELAY_WIFIH_
#define _AKANE_RELAY_WIFIH_

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

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
    
    ESP8266WebServer* server;

    const char* AP_PWD = "5X%r2@MH+Dpbl:1Y2[}'";
    
  public:
    Akane_Observer_Wifi(bool is_connected) {
      should_be_connected = is_connected; 

      prev_status = WL_IDLE_STATUS;
      prev_ip_address = "0.0.0.0";

      WiFi.hostname(Akane_Settings::getInstance().get_hostname());
      
      WiFi.softAP(String("ESP_" + Akane_Settings::getInstance().get_hostname()).c_str(), AP_PWD);

      if (!MDNS.begin(Akane_Settings::getInstance().get_hostname().c_str())) { // Start the mDNS responder for esp8266.local
        Akane_Logger::log("[Akane_Relay_Wifi][mDNS] Error setting up MDNS responder");
      }
      else {
        Akane_Logger::log("[Akane_Relay_Wifi][mDNS] MDNS responder started");
      }

      server = new ESP8266WebServer(ESP8266_PORT); 
      server->on("/", std::bind(&Akane_Observer_Wifi::handleRoot, this));
      server->on("/config", std::bind(&Akane_Observer_Wifi::handleConfig, this));
      server->on("/info", std::bind(&Akane_Observer_Wifi::handleInfo, this));
      server->onNotFound(std::bind(&Akane_Observer_Wifi::handleNotFound, this));
      
      server->begin();
      Serial.println("[Akane_Relay_Wifi] HTTP server started!");
    };
    inline void handleRoot() {
      server->send(200, "text/plain", "Hello from " + Akane_Settings::getInstance().get_hostname());
    };
    inline void handleConfig() {
      String message = "Settings\n\n";
      message += "URI: ";
      message += server->uri();
      message += "\nMethod: ";
      message += (server->method() == HTTP_GET) ? "GET" : "POST";
      message += "\nArguments: ";
      message += server->args();
      message += "\n";

      bool has_update = false;
      for (uint8_t i = 0; i < server->args(); i++) {
        if(server->argName(i) != NULL && server->argName(i).length() > 0 && server->arg(i) != NULL && server->arg(i).length() > 0) {
          message += " " + server->argName(i) + ": " + server->arg(i);
          if(server->argName(i) == "hostname") {
            Akane_Settings::getInstance().set_hostname((char*) server->arg(i).c_str());
            message += " > OK!";
            has_update = true;
          }
          else if(server->argName(i) == "ssid") {
            Akane_Settings::getInstance().set_ssid((char*) server->arg(i).c_str());
            message += " > OK!";
            has_update = true;
          }
          else if(server->argName(i) == "ssid_pwd") {
            Akane_Settings::getInstance().set_ssid_pwd((char*) server->arg(i).c_str());
            message += " > OK!";
            has_update = true;
          }
          else if(server->argName(i) == "mqtt_address") {
            Akane_Settings::getInstance().set_mqtt_address((char*) server->arg(i).c_str());
            message += " > OK!";
            has_update = true;
          }
          
          message += "\n";
        }
      }

      int res_code = 200;
      if(has_update) {
        bool res = Akane_Settings::getInstance().save();
        Akane_Logger::log("[Akane_Relay_Wifi][handleConfig] Saving settings..." + String(res));
      }
      else {
        res_code = 302;
        Akane_Logger::log("[Akane_Relay_Wifi][handleConfig] Nothing to change");
      }
      
      server->send(res_code, "text/plain", message);
    };
    inline void handleInfo() {
      String message = "Information\n\n";
      message += "URI: ";
      message += server->uri();
      message += "\nMethod: ";
      message += (server->method() == HTTP_GET) ? "GET" : "POST";
      message += "\nSettings:\n";

      message += " hostname: " + Akane_Settings::getInstance().get_hostname() + "\n";
      message += " ssid: " + Akane_Settings::getInstance().get_ssid() + "\n";
      message += " ssid_pwd: " + Akane_Settings::getInstance().get_ssid_pwd() + "\n";
      message += " mqtt_address: " + Akane_Settings::getInstance().get_mqtt_address() + "\n";

      message += " wifi_ap_pwd (readonly): " + String(AP_PWD) + "\n";
      
      server->send(200, "text/plain", message);
    };
    inline void handleNotFound(){
      String message = "File Not Found\n\n";
      message += "URI: ";
      message += server->uri();
      message += "\nMethod: ";
      message += (server->method() == HTTP_GET) ? "GET" : "POST";
      message += "\nArguments: ";
      message += server->args();
      message += "\n";
      for (uint8_t i = 0; i < server->args(); i++) {
        message += " " + server->argName(i) + ": " + server->arg(i) + "\n";
      }
      server->send(404, "text/plain", message);
    };
    inline void setActive(bool pActive) {
      should_be_connected = pActive;
      
      if(pActive && !isActive()) {
        Akane_Logger::log("[Akane_Relay_Wifi][setActive] Wifi is not active. Tring to connect...");

        Akane_Logger::log("[Akane_Relay_Wifi][setActive] SSID:    " + Akane_Settings::getInstance().get_ssid());
        Akane_Logger::log("[Akane_Relay_Wifi][setActive] SSID_PWD:" + Akane_Settings::getInstance().get_ssid_pwd());
        
        WiFi.begin(Akane_Settings::getInstance().get_ssid().c_str(), Akane_Settings::getInstance().get_ssid_pwd().c_str());
        
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

      server->handleClient();
    };
};

#endif
