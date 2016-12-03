#ifndef _AKANE_SENSOR_H_
#define _AKANE_SENSOR_H_

#include "Akane_Settings.h"
#include "Akane_Logger.h"
#include "Observable.h" // https://gist.github.com/obedrios/3109063

class Akane_Sensor : public Observable<Akane_Sensor> {
  protected:
    float value;
    String name;
  
  public:
    Akane_Sensor();
    Akane_Sensor(String name);

    void set_name(String name);
    String get_name();
    
    inline virtual void read_value() { 
      Akane_Logger::log("[Akane_Sensor] Notifying observers...");
      notifyObservers();
    };
    float get_value();
};

#endif
