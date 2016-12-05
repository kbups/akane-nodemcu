#ifndef _AKANE_OBSERVER_TEMPH_
#define _AKANE_OBSERVER_TEMPH_

#include "Akane_Sensor.h"
#include "Akane_Logger.h"
#include "Observer.h"

class Akane_Observer_Temp : public Observer<Akane_Sensor> {
  private:
    float prev_temp;
    
  public:
    Akane_Observer_Temp() {
      prev_temp = TEMP_NOVALUE;
    };
    inline virtual void update(Akane_Sensor *observable) {
      float res = observable->get_value();
      Akane_Logger::log("[Akane_Observer_Temp][update] Receive value is: " + String(res));

      Akane_Screen::getInstance().display_temperature(res, prev_temp);
      prev_temp = res;
    };
};

#endif
