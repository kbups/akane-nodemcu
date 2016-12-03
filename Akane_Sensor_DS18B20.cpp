#include "Akane_Sensor_DS18B20.h"

void Akane_Sensor_DS18B20::read_value() {
  Akane_Logger::log("[Akane_Sensor_DS18B20] Reading sensor value...");

  OneWire oneWire(pin);
  DallasTemperature DS18B20(&oneWire);
  DS18B20.requestTemperaturesByIndex(index);
  float temp = DS18B20.getTempCByIndex(index);
  
  this->value = temp;
  Akane_Sensor::read_value(); // notify observers
}

