#ifndef _AKANE_SENSOR_WIFI_H_
#define _AKANE_SENSOR_WIFI_H_

#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include "Akane_Sensor.h"
#include "Akane_Logger.h"

class Akane_Sensor_Wifi : public Akane_Sensor {
  private:
    
  public:
    Akane_Sensor_Wifi() : Akane_Sensor_Wifi("WIFI") { };
    Akane_Sensor_Wifi(String name) : Akane_Sensor(name, 0) { };
    
    inline virtual void read_value() {
      Akane_Logger::log("[Akane_Sensor_Wifi] Reading Wifi status...");
    
      uint8_t res = WiFi.status();
      
      this->value = (float) res;
      Akane_Sensor::read_value(); // notify observers;
    };
};

#endif
