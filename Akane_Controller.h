#ifndef _AKANE_CONTROLLERH_
#define _AKANE_CONTROLLERH_

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "Akane_Settings.h"
#include "Akane_Sensor.h"

class Akane_Controller {
  public:
    Akane_Settings* settings;
    Akane_Sensor* sensors;

  public:
    Akane_Controller(Akane_Settings* psettings, Akane_Sensor pSensors[]);
    void initialize();
    void execute();
    
    IPAddress getLocalIP();

  private:
    void connect();
  
};

#endif
