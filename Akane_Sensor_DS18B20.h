#ifndef _AKANE_SENSOR_DS18B20_H_
#define _AKANE_SENSOR_DS18B20_H_

#include "Akane_Sensor.h"
#include "Akane_Logger.h"

/** DS18B20 **/
#include <OneWire.h>
#include <DallasTemperature.h>

class Akane_Sensor_DS18B20 : public Akane_Sensor {
  private:
    unsigned int pin;
    unsigned int index;
    
  public:
    Akane_Sensor_DS18B20(unsigned int pin, unsigned int index) : Akane_Sensor_DS18B20(pin, index, "DS18B20") { };
    Akane_Sensor_DS18B20(unsigned int pin, unsigned int index, String name) : Akane_Sensor(name) { this->pin = pin; this->index = index; };

    //void set_name(String name);
    //String get_name();
    
    virtual void read_value();
    //float get_value();
};

#endif
