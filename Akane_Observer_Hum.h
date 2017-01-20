#ifndef _AKANE_OBSERVER_HUMH_
#define _AKANE_OBSERVER_HUMH_

#include "Akane_Sensor.h"
#include "Akane_Logger.h"
#include "Observer.h"

class Akane_Observer_Hum : public Observer<Akane_Sensor> {
  private:
    float prev_hum;
    
  public:
    Akane_Observer_Hum() {
      prev_hum = -1;
    };
    inline virtual void update(Akane_Sensor *observable) {
      float res = HUM_MAXVALUE;
      if(observable->get_nbvalues() > 1)
        res = observable->get_value1();
      Akane_Logger::log("[Akane_Observer_Hum][update] Receive value is: " + String(res));

      Akane_Screen::getInstance().display_humidity(res, prev_hum);
      prev_hum = res;
    };
};

#endif
