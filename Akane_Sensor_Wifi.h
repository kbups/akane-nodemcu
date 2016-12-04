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
    Akane_Sensor_Wifi(String name) : Akane_Sensor(name) { };
    
    virtual void read_value();
};

#endif
