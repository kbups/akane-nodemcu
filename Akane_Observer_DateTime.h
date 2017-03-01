#ifndef _AKANE_OBSERVER_DATETIMEH_
#define _AKANE_OBSERVER_DATETIMEH_

#include "Akane_Sensor.h"
#include "Akane_Logger.h"
#include "Observer.h"
#include "Akane_Observer_DateTime.h"

class Akane_Observer_DateTime : public Observer<Akane_Sensor> {
  private:
    short prev_hour;
    short prev_minute;
    short prev_second;
  public:
    Akane_Observer_DateTime() {
    };
    inline virtual void update(Akane_Sensor *observable) {
      RtcDateTime res;
      if(observable->get_nbvalues() == 3) {
        res = ((Akane_Sensor_DS1307*) observable)->get_datetime();
        Akane_Logger::log("[Akane_Observer_DateTime][update] Receive value is: " + String(res));

        if(res) {
          /*dt.Month(),
          dt.Day(),
          dt.Year(),
          dt.Hour(),
          dt.Minute(),
          dt.Second())*/
          short hour = res.Hour();
          short minute = res.Minute();
          short second = res.Second();
          Akane_Screen::getInstance().update_time(hour, minute, second, prev_hour, prev_minute, prev_second);

          prev_hour = hour;
          prev_minute = minute;
          prev_second = second;
        }
      }
      else {
        Akane_Logger::log("[Akane_Observer_DateTime][update] Invalid sensor. It must be a DS1307 chip");
      }
    };
};

#endif
