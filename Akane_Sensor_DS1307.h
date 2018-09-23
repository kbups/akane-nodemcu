#ifndef _AKANE_SENSOR_DS1307_H_
#define _AKANE_SENSOR_DS1307_H_

#include "Akane_Sensor.h"
#include "Akane_Logger.h"

/** DS1307 **/
#include <pgmspace.h>
#include <Wire.h>
#include <RtcDS1307.h>

#define countof(a) (sizeof(a) / sizeof(a[0]))

class Akane_Sensor_DS1307 : public Akane_Sensor {
  private:
    RtcDS1307 rtc;

   protected:
    //float value; // Not used
    //float value1; // Not used
    RtcDateTime now;
    
  public:
    Akane_Sensor_DS1307() : Akane_Sensor_DS1307("DS1307") { };
    Akane_Sensor_DS1307(String name) : Akane_Sensor(name, 0) { 
      this->nbvalues = 3;

      rtc.Begin();
      Wire.begin(DS1307_SDA, DS1307_SCL);

      RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
      Akane_Logger::log("[Akane_Sensor_DS1307] Get compiled datetime...");
      printDateTime(compiled);
      
      if (!rtc.IsDateTimeValid()) {
        // Common Causes:
        //    1) first time you ran and the device wasn't running yet
        //    2) the battery on the device is low or even missing

        Akane_Logger::log("[Akane_Sensor_DS1307] RTC lost confidence in the DateTime!");

        // following line sets the RTC to the date & time this sketch was compiled
        // it will also reset the valid flag internally unless the Rtc device is
        // having an issue

        //rtc.SetDateTime(compiled);
        set_datetime(compiled);
      }

      if (!rtc.GetIsRunning()) {
        Akane_Logger::log("[Akane_Sensor_DS1307] RTC was not actively running, starting now");
        rtc.SetIsRunning(true);
      }

      RtcDateTime now_init = rtc.GetDateTime();
      if (now_init < compiled) {
        Akane_Logger::log("[Akane_Sensor_DS1307] RTC is older than compile time!  (Updating DateTime)");
        rtc.SetDateTime(compiled);
      }
      else if (now_init > compiled) {
        Akane_Logger::log("[Akane_Sensor_DS1307] RTC is newer than compile time. (this is expected)");
      }
      else if (now_init == compiled) {
        Akane_Logger::log("[Akane_Sensor_DS1307] RTC is the same as compile time! (not expected but all is fine)");
      }

      // never assume the Rtc was last configured by you, so
      // just clear them to your needed state
      rtc.SetSquareWavePin(DS1307SquareWaveOut_Low); 
    };

    void set_datetime(RtcDateTime dt_value) {
      if(dt_value) {
        Akane_Logger::log("[Akane_Sensor_DS1307] Updating the datetime...");
        rtc.SetDateTime(dt_value);
        printDateTime(dt_value);
      }
    };
    
    virtual void read_value() {
      Akane_Logger::log("[Akane_Sensor_DS1307] Reading sensor value...");
      
      if (!rtc.IsDateTimeValid()) {
        // Common Causes:
        //    1) the battery on the device is low or even missing and the power line was disconnected
        Akane_Logger::log("[Akane_Sensor_DS1307] RTC lost confidence in the DateTime!");
      }

      Akane_Logger::log("[Akane_Sensor_DS1307] Received datetime is...");
      this->now = rtc.GetDateTime();
      printDateTime(now);

      Akane_Sensor::read_value(); // notify observers
    };

    RtcDateTime get_datetime() {
      return now;
    };

  private:
    void printDateTime(const RtcDateTime& dt) {
      char datestring[20];
    
      snprintf_P(datestring,
        countof(datestring),
        PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
        dt.Month(),
        dt.Day(),
        dt.Year(),
        dt.Hour(),
        dt.Minute(),
        dt.Second());

      Akane_Logger::log("[Akane_Sensor_DS1307] DateTime = " + String(datestring));
    };
};

#endif
