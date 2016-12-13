#ifndef _AKANE_RELAY_HEATERH_
#define _AKANE_RELAY_HEATERH_

#include "Akane_Settings.h"
#include "Akane_Logger.h"
#include "Observer.h"
#include "Akane_Relay.h"

class Akane_Relay_Heater : public Akane_Relay {
  private:
  
  public:
    Akane_Relay_Heater(int pPin): Akane_Relay(pPin) { };
    inline virtual void update(Akane_Sensor *observable) {
      uint8_t res = (uint8_t) observable->get_value();
      Akane_Logger::log("[Akane_Relay_Heater][update] Receive value is: " + String(res));
      
      //if((res != WL_CONNECTED && should_be_connected) || (res != WL_DISCONNECTED && !should_be_connected)) {
      //  setActive(should_be_connected);
      //}

      //String ip_address = getLocalIP();
        
      //if(prev_status != res || prev_ip_address != ip_address) {
        //Akane_Logger::log("[Akane_Relay_Heater][update] Status has changed: " + String(prev_status) + " to " + String(res) + " AND " + prev_ip_address + " to " + ip_address);
        //Akane_Screen::getInstance().display_fan_status(res == WL_CONNECTED, ip_address, prev_ip_address);
      //}
      //prev_status = res;
      //prev_ip_address = ip_address;
      //status = res;
    };
};

#endif
