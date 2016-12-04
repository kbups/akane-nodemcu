#include "Akane_Sensor_Wifi.h"

void Akane_Sensor_Wifi::read_value() {
  Akane_Logger::log("[Akane_Sensor_Wifi] Reading Wifi status...");

  uint8_t res = WiFi.status();
  
  this->value = (float) res;
  Akane_Sensor::read_value(); // notify observers
}

