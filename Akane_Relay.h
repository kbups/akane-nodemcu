#ifndef _AKANE_RELAYH_
#define _AKANE_RELAYH_

#include "Akane_Settings.h"
#include "Akane_Sensor.h"
#include "Akane_Logger.h"
#include "Observer.h"

#define UNSIGNED_LONG_MAX 4294967295

class Akane_Relay : public Observer<Akane_Sensor> {
  protected:
    int pin;
    bool pin_status;
    unsigned long prev_change;
    unsigned int min_change_delay_on;
    unsigned int min_change_delay_off;
    
  public:
    Akane_Relay(int pPin, unsigned int pMin_change_delay_on, unsigned int pMin_change_delay_off);
    void setActive(bool pActive);
    void setActive(bool pActive, bool pForce);
    bool isActive();
    void set_min_delays(unsigned int pMin_change_delay_on, unsigned int pMin_change_delay_off);
    virtual void update(Akane_Sensor *observable);
};

#endif
