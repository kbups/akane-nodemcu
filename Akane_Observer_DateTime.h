#ifndef _AKANE_OBSERVER_DATETIMEH_
#define _AKANE_OBSERVER_DATETIMEH_

#include "Akane_Sensor.h"
#include "Akane_Logger.h"
#include "Observer.h"
#include "Akane_Observer_DateTime.h"

class Akane_Observer_DateTime : public Observer<Akane_Sensor> {
  private:
    
  public:
    Akane_Observer_DateTime() {
    };
    inline virtual void update(Akane_Sensor *observable) {
      RtcDateTime res;
      if(observable->get_nbvalues() == 3) {
        res = ((Akane_Sensor_DS1307*) observable)->get_datetime();
        Akane_Logger::log("[Akane_Observer_DateTime][update] Receive value is: " + String(res));

        //Akane_Screen::getInstance().display_datetime(res);
      }
      else {
        Akane_Logger::log("[Akane_Observer_DateTime][update] Invalid sensor. It must be a DS1307 chip");
      }
    };
};

#endif
