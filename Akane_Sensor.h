#ifndef _AKANE_SENSOR_H_
#define _AKANE_SENSOR_H_

#include "Akane_Settings.h"
#include "Akane_Logger.h"
#include "Observable.h" // https://gist.github.com/obedrios/3109063

class Akane_Sensor : public Observable<Akane_Sensor> {
  protected:
    String name;
    unsigned int nbvalues;
    float value;
    float value1;
    unsigned long prev_measure;
    unsigned int interval;
  
  public:
    Akane_Sensor() : Akane_Sensor("UNDEFINED", 0) { };
    Akane_Sensor(String name, unsigned int interval) {
      this->set_name(name);
      this->nbvalues = 1;
      prev_measure = 0;
      this->interval = interval;
    };

    inline void set_name(String name) {
      this->name = name;
    };
    inline String get_name() {
      return this->name;
    };
    
    inline virtual void read_value() { 
      Akane_Logger::log("[Akane_Sensor] Notifying observers...");
      notifyObservers();
    };
    inline short int get_nbvalues(){
      return this->nbvalues;
    };
    inline void set_nbvalues(short int count) {
      this->nbvalues = count;
    };
    inline float get_value() {
      return this->value;
    };
    inline float get_value1() {
      return this->value1;
    };
  
    inline bool has_measure_expired() {
      unsigned long t = millis();
    
      unsigned long t_delay = 0;
      if(t < prev_measure) {
        t_delay = t + (UNSIGNED_LONG_MAX - prev_measure);
      }
      else {
        t_delay = t - prev_measure;
      }
    
      return t_delay > interval;
    };
};

#endif
