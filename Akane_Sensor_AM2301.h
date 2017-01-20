#ifndef _AKANE_SENSOR_AM2301_H_
#define _AKANE_SENSOR_AM2301_H_

#include "Akane_Sensor.h"
#include "Akane_Logger.h"

/** AM2301 **/
#include "DHT.h"

#define DHTTYPE DHT21   // DHT 21 (AM2301)

class Akane_Sensor_AM2301 : public Akane_Sensor {
  private:
    unsigned int pin;
    unsigned int index;

   protected:
    //float value; // Temperature (by inheritance)
    //float value1; // Humidity
    
  public:
    Akane_Sensor_AM2301(unsigned int pin) : Akane_Sensor_AM2301(pin, "AM2301") { };
    Akane_Sensor_AM2301(unsigned int pin, String name) : Akane_Sensor(name) { this->pin = pin; this->nbvalues = 2; };
    
    virtual void read_value() {
      Akane_Logger::log("[Akane_Sensor_AM2301] Reading sensor value...");

      DHT dht(pin, DHTTYPE);
      dht.begin();

      float hum = dht.readHumidity();
      if(hum < HUM_MINVALUE || hum >= HUM_MAXVALUE) {
        Akane_Logger::log("[Akane_Sensor_AM2301] Received humidity is not valid");
        hum = HUM_MAXVALUE;
      }
      else {
        Akane_Logger::log("[Akane_Sensor_AM2301] Received humidity is " + String(hum));
      }
      this->value1 = hum;

      float temp = dht.readTemperature();
      if(temp < TEMP_MINVALUE || temp >= TEMP_MAXVALUE) {
        Akane_Logger::log("[Akane_Sensor_AM2301] Received temperature is not valid");
        temp = TEMP_MAXVALUE;
      }
      else {
        Akane_Logger::log("[Akane_Sensor_AM2301] Received temperature is " + String(temp));
      }
      this->value = temp;
      
      Akane_Sensor::read_value(); // notify observers
    }
};

#endif
