#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "Akane_Settings.h"
#include "Akane_Screen.h"
#include "Akane_Logger.h"
#include "Akane_Sensor.h"
#include "Akane_Sensor_Wifi.h"
#include "Akane_Sensor_DS1307.h"
#include "Akane_Observer_Wifi.h"
#include "Akane_Observer_MQTT.h"
#include "Akane_Observer_DateTime.h"

Akane_Sensor_Wifi* sensor_wifi;
Akane_Sensor_DS1307* sensor_ds1307;
Akane_Observer_Wifi* observer_wifi;
Akane_Observer_MQTT* observer_mqtt;
Akane_Observer_DateTime* observer_datetime;

void setup() {
  Akane_Logger::initialize();
  Akane_Logger::log("Initializing...");

  Akane_Settings::getInstance().load();
  
  Akane_Screen::getInstance().initialize();

  sensor_wifi = new Akane_Sensor_Wifi("Wifi");
  sensor_ds1307 = new Akane_Sensor_DS1307("DS1307");

  observer_wifi = new Akane_Observer_Wifi(true);
  observer_mqtt = new Akane_Observer_MQTT();
  observer_datetime = new Akane_Observer_DateTime();
  
  sensor_wifi->addObserver(*observer_wifi);
  sensor_ds1307->addObserver(*observer_datetime);
}

void loop() {
  sensor_wifi->read_value();
  sensor_ds1307->read_value();
  observer_mqtt->read_value();
  
  Serial.printf("Heap size: %u\n", ESP.getFreeHeap());
  delay(250);
}


