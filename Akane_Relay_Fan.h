#ifndef _AKANE_RELAY_FANH_
#define _AKANE_RELAY_FANH_

#include "Akane_Settings.h"
#include "Akane_Logger.h"
#include "Observer.h"
#include "Akane_Relay.h"

class Akane_Relay_Fan : public Akane_Relay {
  private:
    bool prev_status;
  
  public:
    Akane_Relay_Fan(int pPin, unsigned int min_change_delay): Akane_Relay(pPin, min_change_delay, min_change_delay) {
      prev_status = false;

      Akane_Screen::getInstance().update_fan_info(Akane_Settings::getInstance().get_fan_instruction());
    };
    
    inline virtual void update(Akane_Sensor *observable) {
      uint8_t res = (uint8_t) observable->get_value();
      Akane_Logger::log("[Akane_Relay_Fan][update] Receive value is: " + String(res));
      
      if(res >= TEMP_MAXVALUE) {
        Akane_Logger::log("[Akane_Relay_Fan][update] Invalid data received. Deactivating relay...");
        setActive(false, true);
      }
      else {
        bool is_active = isActive();
        short instruction = Akane_Settings::getInstance().get_fan_instruction();
        if(res >= instruction && !is_active) {
          Akane_Logger::log("[Akane_Relay_Fan][update] Activating relay...");
          setActive(true);
        }
        else if(res < instruction && is_active) {
          Akane_Logger::log("[Akane_Relay_Fan][update] Deactivating relay...");
          setActive(false);
        }
      }

      if(prev_status != pin_status) {
        Akane_Logger::log("[Akane_Relay_Fan][update] Status has changed: " + String(prev_status) + " to " + String(pin_status));
        Akane_Screen::getInstance().update_fan_status(pin_status);
      
        prev_status = pin_status;
      }
    };
};

#endif
