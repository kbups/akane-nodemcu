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
  
  public:
    Akane_Sensor();
    Akane_Sensor(String name);

    void set_name(String name);
    String get_name();
    
    inline virtual void read_value() { 
      Akane_Logger::log("[Akane_Sensor] Notifying observers...");
      notifyObservers();
    };
    short int get_nbvalues();
    void set_nbvalues(short int count);
    float get_value();
    float get_value1();
};

#endif
