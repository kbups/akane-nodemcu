#ifndef _AKANE_RELAY_HUMH_
#define _AKANE_RELAY_HUMH_

#include "Akane_Settings.h"
#include "Akane_Logger.h"
#include "Observer.h"
#include "Akane_Relay.h"

class Akane_Relay_Hum : public Akane_Relay {
  private:
    bool prev_status;
    unsigned int max_duration;
  
  public:
    Akane_Relay_Hum(int pPin, unsigned int pMin_change_delay_on, unsigned int pMin_change_delay_off): Akane_Relay(pPin, pMin_change_delay_on, pMin_change_delay_off) {
      prev_status = false;
      max_duration = pMin_change_delay_on;

      //Akane_Screen::getInstance().update_fogger_info(Akane_Settings::getInstance().get_hum_instruction());
    };
    
    inline virtual void update(Akane_Sensor *observable) {
      float res = (float) observable->get_value1();
      Akane_Logger::log("[Akane_Relay_Hum][update] Receive value is: " + String(res));
      
      if(res >= TEMP_MAXVALUE) {
        Akane_Logger::log("[Akane_Relay_Hum][update] Invalid data received. Deactivating relay...");
        setActive(false, true);
      }
      else {
        // Get elapsed time
        unsigned long t = millis();

        unsigned long t_delay = 0;
        if(t < prev_change) {
          t_delay = t + (UNSIGNED_LONG_MAX - prev_change);
        }
        else {
          t_delay = t - prev_change;
        }
        
        bool is_active = isActive();

        //Akane_Logger::log("[Akane_Relay_Hum][update] is_active = " + String(is_active));
        //Akane_Logger::log("[Akane_Relay_Hum][update] t_delay = " + String(t_delay));
        //Akane_Logger::log("[Akane_Relay_Hum][update] max_duration = " + String(max_duration));
        
        if(is_active && t_delay >= min_change_delay_on) {
          Akane_Logger::log("[Akane_Relay_Hum][update] Force relay deactivation...");
          setActive(false, true);
        }
        else {
          short instruction = Akane_Settings::getInstance().get_hum_instruction();
          
          if(res >= instruction && is_active) {
            Akane_Logger::log("[Akane_Relay_Hum][update] Deactivating relay...");
            setActive(false, true);
          }
          else if(res < instruction && !is_active) {
            Akane_Logger::log("[Akane_Relay_Hum][update] Activating relay...");
            setActive(true);
          }
        }
      }

      if(prev_status != pin_status) {
        Akane_Logger::log("[Akane_Relay_Hum][update] Status has changed: " + String(prev_status) + " to " + String(pin_status));
        //Akane_Screen::getInstance().update_fogger_status(pin_status);
      
        prev_status = pin_status;
      }
    };
};

#endif
